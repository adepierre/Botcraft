#if PROTOCOL_VERSION > 340
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundCustomQueryPacket : public BaseMessage<ServerboundCustomQueryPacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x02;
        }

        virtual const std::string GetName() const override
        {
            return "Custom Query";
        }

        virtual ~ServerboundCustomQueryPacket() override
        {

        }

        void SetTransactionId(const int transaction_id_)
        {
            transaction_id = transaction_id_;
        }

        void SetData(const std::optional<std::vector<unsigned char>>& data_)
        {
            data = data_;
        }

        const int GetTransationId() const
        {
            return transaction_id;
        }

        const std::optional<std::vector<unsigned char>>& GetData() const
        {
            return data;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            transaction_id = ReadData<VarInt>(iter, length);
            data = ReadOptional<std::vector<unsigned char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadByteArray(i, l, l);
                }
            );
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(transaction_id, container);
            WriteOptional<std::vector<unsigned char>>(data, container,
                [](const std::vector<unsigned char>& v, WriteContainer& c)
                {
                    WriteByteArray(v, c);
                }
            );
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["transaction_id"] = transaction_id;
            if (data.has_value())
            {
                output["data"] = "Vector of " + std::to_string(data.value().size()) + " unsigned char";
            }

            return output;
        }

    private:
        int transaction_id;
        std::optional<std::vector<unsigned char>> data;
    };
} // ProtocolCraft
#endif
