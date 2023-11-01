#pragma once
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundCustomQueryAnswerPacket : public BaseMessage<ServerboundCustomQueryAnswerPacket>
    {
    public:
        static constexpr int packet_id = 0x02;
        static constexpr std::string_view packet_name = "Custom Query Answer";

        virtual ~ServerboundCustomQueryAnswerPacket() override
        {

        }

        void SetTransactionId(const int transaction_id_)
        {
            transaction_id = transaction_id_;
        }

        void SetPayload(const std::optional<std::vector<unsigned char>>& payload_)
        {
            payload = payload_;
        }

        int GetTransationId() const
        {
            return transaction_id;
        }

        const std::optional<std::vector<unsigned char>>& GetPayload() const
        {
            return payload;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            transaction_id = ReadData<VarInt>(iter, length);
            payload = ReadOptional<std::vector<unsigned char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadByteArray(i, l, l);
                }
            );
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(transaction_id, container);
            WriteOptional<std::vector<unsigned char>>(payload, container,
                [](const std::vector<unsigned char>& v, WriteContainer& c)
                {
                    WriteByteArray(v, c);
                }
            );
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["transaction_id"] = transaction_id;
            if (payload.has_value())
            {
                output["payload"] = "Vector of " + std::to_string(payload.value().size()) + " unsigned char";
            }

            return output;
        }

    private:
        int transaction_id = 0;
        std::optional<std::vector<unsigned char>> payload;
    };
} // ProtocolCraft
#endif
