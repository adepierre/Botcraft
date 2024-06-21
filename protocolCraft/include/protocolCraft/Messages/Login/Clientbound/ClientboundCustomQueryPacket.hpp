#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomQueryPacket : public BaseMessage<ClientboundCustomQueryPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Custom Query";

        DECLARE_FIELDS(
            (VarInt,        Identifier, std::vector<unsigned char>),
            (TransactionId, Identifier, Data)
        );
        DECLARE_SERIALIZE;

        GETTER_SETTER(TransactionId);
        GETTER_SETTER(Identifier);
        GETTER_SETTER(Data);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetTransactionId(ReadData<VarInt>(iter, length));
            SetIdentifier(ReadData<Identifier>(iter, length));
            SetData(ReadByteArray(iter, length, length));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetTransactionId(), container);
            WriteData<Identifier>(GetIdentifier(), container);
            WriteByteArray(GetData(), container);
        }
    };
} //ProtocolCraft
#endif
