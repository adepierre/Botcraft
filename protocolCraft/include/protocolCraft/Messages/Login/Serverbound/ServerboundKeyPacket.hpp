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

        virtual ~ServerboundKeyPacket() override
        {

        }

        void SetKeyBytes(const std::vector<unsigned char> &key_bytes_)
        {
            key_bytes = key_bytes_;
        }

        void SetNonce(const std::vector<unsigned char>& nonce_)
        {
            nonce = nonce_;
        }

#if PROTOCOL_VERSION > 758
        void SetHasSaltSignature(const bool has_salt_signature_)
        {
            has_salt_signature = has_salt_signature_;
        }

        void SetHasSignature(const std::pair<long long int, std::vector<unsigned char> >& salt_signature_)
        {
            salt_signature = salt_signature_;
        }
#endif

        const std::vector<unsigned char>& GetKeyBytes() const
        {
            return key_bytes;
        }

        const std::vector<unsigned char>& GetNonce() const
        {
            return nonce;
        }

#if PROTOCOL_VERSION > 758
        const bool GetHasSaltSignature() const
        {
            return has_salt_signature;
        }

        const std::pair<long long int, std::vector<unsigned char> >& GetSaltSignature() const
        {
            return salt_signature;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            int key_bytes_length = ReadData<VarInt>(iter, length);
            key_bytes = ReadByteArray(iter, length, key_bytes_length);
#if PROTOCOL_VERSION > 758
            has_salt_signature = ReadData<bool>(iter, length);
            if (has_salt_signature)
            {
                salt_signature.first = ReadData<long long int>(iter, length);
                salt_signature.second = ReadByteArray(iter, length, length);
            }
            else
            {
                int nonce_length = ReadData<VarInt>(iter, length);
                nonce = ReadByteArray(iter, length, nonce_length);
            }
#else
            int nonce_length = ReadData<VarInt>(iter, length);
            nonce = ReadByteArray(iter, length, nonce_length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(key_bytes.size(), container);
            WriteByteArray(key_bytes, container);
#if PROTOCOL_VERSION > 758
            WriteData<bool>(has_salt_signature, container);
            if (has_salt_signature)
            {
                WriteData<long long int>(salt_signature.first, container);
                WriteByteArray(salt_signature.second, container);
            }
            else
            {
                WriteData<VarInt>(nonce.size(), container);
                WriteByteArray(nonce, container);
            }
#else
            WriteData<VarInt>(nonce.size(), container);
            WriteByteArray(nonce, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["key_bytes"] = "vector of " + std::to_string(key_bytes.size()) + " unsigned char";
#if PROTOCOL_VERSION > 758
            if (has_salt_signature)
            {
                output["salt_signature"] = { {"salt", salt_signature.first}, {"signature", "vector of " + std::to_string(salt_signature.second.size()) + " unsigned char"} };
            }
            else
            {
                output["nonce"] = "vector of " + std::to_string(nonce.size()) + " unsigned char";
            }
#else
            output["nonce"] = "vector of " + std::to_string(nonce.size()) + " unsigned char";
#endif

            return output;
        }

    private:
        std::vector<unsigned char> key_bytes;
        std::vector<unsigned char> nonce;
#if PROTOCOL_VERSION > 758
        bool has_salt_signature;
        std::pair<long long int, std::vector<unsigned char> > salt_signature;
#endif
    };
} // Botcraft