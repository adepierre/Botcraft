#if PROTOCOL_VERSION > 340
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomQueryPacket : public BaseMessage<ClientboundCustomQueryPacket>
    {
    public:
        static constexpr int packet_id = 0x04;
        static constexpr std::string_view packet_name = "Custom Query";

        virtual ~ClientboundCustomQueryPacket() override
        {

        }

        
        void SetTransactionId(const int transaction_id_)
        {
            transaction_id = transaction_id_;
        }

        void SetIdentifier(const Identifier& identifier_)
        {
            identifier = identifier_;
        }

        void SetData(const std::vector<unsigned char>& data_)
        {
            data = data_;
        }


        int GetTransactionId() const
        {
            return transaction_id;
        }

        const Identifier& GetIdentifier() const
        {
            return identifier;
        }

        const std::vector<unsigned char>& GetData() const
        {
            return data;
        }


    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            transaction_id = ReadData<VarInt>(iter, length);
            identifier = ReadData<Identifier>(iter, length);
            data = ReadByteArray(iter, length, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(transaction_id, container);
            WriteData<Identifier>(identifier, container);
            WriteByteArray(data, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["transaction_id"] = transaction_id;
            output["identifier"] = identifier.Serialize();
            output["data"] = "Vector of " + std::to_string(data.size()) + " unsigned char";


            return output;
        }

    private:
        int transaction_id;
        Identifier identifier;
        std::vector<unsigned char> data;
    };
} //ProtocolCraft
#endif
