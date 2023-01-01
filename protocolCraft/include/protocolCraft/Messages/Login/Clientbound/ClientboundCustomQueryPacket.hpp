#if PROTOCOL_VERSION > 340
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomQueryPacket : public BaseMessage<ClientboundCustomQueryPacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x04;
        }

        virtual const std::string GetName() const override
        {
            return "Custom Query";
        }

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


        const int GetTransactionId() const
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
            WriteArrayData(data, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

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
