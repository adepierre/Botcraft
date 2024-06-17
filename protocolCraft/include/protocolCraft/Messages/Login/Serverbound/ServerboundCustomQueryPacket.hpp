#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundCustomQueryPacket : public BaseMessage<ServerboundCustomQueryPacket>
    {
    public:
        static constexpr int packet_id = 0x02;
        static constexpr std::string_view packet_name = "Custom Query";

        DECLARE_FIELDS(
            (VarInt,        std::optional<std::vector<unsigned char>>),
            (TransactionId, Data)
        );
        DECLARE_SERIALIZE;

        GETTER_SETTER(TransactionId);
        GETTER_SETTER(Data);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetTransactionId(ReadData<VarInt>(iter, length));
            // special case, read all remaining bytes
            SetData(ReadOptional<std::vector<unsigned char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadByteArray(i, l, l);
                }
            ));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetTransactionId(), container);
            // special case, write all bytes without size prefix
            WriteOptional<std::vector<unsigned char>>(GetData(), container,
                [](const std::vector<unsigned char>& v, WriteContainer& c)
                {
                    WriteByteArray(v, c);
                }
            );
        }
    };
} // ProtocolCraft
#endif
