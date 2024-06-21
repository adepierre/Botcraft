#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundCustomQueryAnswerPacket : public BaseMessage<ServerboundCustomQueryAnswerPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Custom Query Answer";

        DECLARE_FIELDS(
            (VarInt,        std::optional<std::vector<unsigned char>>),
            (TransactionId, Payload)
        );
        DECLARE_SERIALIZE;

        GETTER_SETTER(TransactionId);
        GETTER_SETTER(Payload);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetTransactionId(ReadData<VarInt>(iter, length));
            // special case, read all remaining bytes
            SetPayload(ReadOptional<std::vector<unsigned char>>(iter, length,
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
            WriteOptional<std::vector<unsigned char>>(GetPayload(), container,
                [](const std::vector<unsigned char>& v, WriteContainer& c)
                {
                    WriteByteArray(v, c);
                }
            );
        }
    };
} // ProtocolCraft
#endif
