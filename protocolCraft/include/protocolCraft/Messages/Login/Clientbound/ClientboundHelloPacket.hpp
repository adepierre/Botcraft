#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHelloPacket : public BaseMessage<ClientboundHelloPacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x01;
        }

        virtual const std::string GetName() const override
        {
            return "Hello";
        }

        virtual ~ClientboundHelloPacket() override
        {

        }

        void SetServerID(const std::string& server_id_)
        {
            server_ID = server_id_;
        }

        void SetPublicKey(const std::vector<unsigned char>& public_key_)
        {
            public_key = public_key_;
        }

        void SetNonce(const std::vector<unsigned char>& nonce_)
        {
            nonce = nonce_;
        }

        const std::string& GetServerID() const
        {
            return server_ID;
        }

        const std::vector<unsigned char>& GetPublicKey() const
        {
            return public_key;
        }

        const std::vector<unsigned char>& GetNonce() const
        {
            return nonce;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            server_ID = ReadData<std::string>(iter, length);
            int public_key_length = ReadData<VarInt>(iter, length);
            public_key = ReadByteArray(iter, length, public_key_length);
            int nonce_length = ReadData<VarInt>(iter, length);
            nonce = ReadByteArray(iter, length, nonce_length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(server_ID, container);
            WriteData<VarInt>(public_key.size(), container);
            WriteByteArray(public_key, container);
            WriteData<VarInt>(nonce.size(), container);
            WriteByteArray(nonce, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["server_ID"] = picojson::value(server_ID);
            object["public_key"] = picojson::value("vector of " + std::to_string(public_key.size()) + " unsigned char");
            object["nonce"] = picojson::value("vector of " + std::to_string(nonce.size()) + " unsigned char");

            return value;
        }

    private:
        std::string server_ID;
        std::vector<unsigned char> public_key;
        std::vector<unsigned char> nonce;
    };
}