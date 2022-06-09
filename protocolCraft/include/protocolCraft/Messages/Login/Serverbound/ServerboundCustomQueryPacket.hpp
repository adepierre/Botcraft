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

        void SetData(const std::vector<unsigned char>& data_)
        {
            data = data_;
        }

        const int GetTransationId() const
        {
            return transaction_id;
        }

        const std::vector<unsigned char>& GetData() const
        {
            return data;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            transaction_id = ReadData<VarInt>(iter, length);
            data.clear();
            if (ReadData<bool>(iter, length))
            {
                data = ReadByteArray(iter, length, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(transaction_id, container);
            if (data.size())
            {
                WriteData<bool>(true, container);
                WriteByteArray(data, container);
            }
            else
            {
                WriteData<bool>(false, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["transaction_id"] = transaction_id;
            output["data"] = "Vector of " + std::to_string(data.size()) + " unsigned char";

            return output;
        }

    private:
        int transaction_id;
        std::vector<unsigned char> data;
    };
} // Botcraft
#endif
