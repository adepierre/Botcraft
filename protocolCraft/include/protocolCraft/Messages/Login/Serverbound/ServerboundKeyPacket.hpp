#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundKeyPacket : public BaseMessage<ServerboundKeyPacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x01;
        }

        virtual const std::string GetName() const override
        {
            return "Key";
        }

        void SetKeyBytes(const std::vector<unsigned char> &key_bytes_)
        {
            key_bytes = key_bytes_;
        }

        void SetNonce(const std::vector<unsigned char>& nonce_)
        {
            nonce = nonce_;
        }

        const std::vector<unsigned char>& GetKeyBytes() const
        {
            return key_bytes;
        }

        const std::vector<unsigned char>& GetNonce() const
        {
            return nonce;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            int key_bytes_length = ReadVarInt(iter, length);
            key_bytes = ReadByteArray(iter, length, key_bytes_length);
            int nonce_length = ReadVarInt(iter, length);
            nonce = ReadByteArray(iter, length, nonce_length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(key_bytes.size(), container);
            WriteByteArray(key_bytes, container);
            WriteVarInt(nonce.size(), container);
            WriteByteArray(nonce, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["key_bytes"] = picojson::value("vector of " + std::to_string(key_bytes.size()) + " unsigned char");
            object["nonce"] = picojson::value("vector of " + std::to_string(nonce.size()) + " unsigned char");

            return value;
        }

    private:
        std::vector<unsigned char> key_bytes;
        std::vector<unsigned char> nonce;
    };
} // Botcraft