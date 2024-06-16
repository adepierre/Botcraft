#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/SaltSignature.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundKeyPacket : public BaseMessage<ServerboundKeyPacket>
    {
    public:
        static constexpr int packet_id = 0x01;
        static constexpr std::string_view packet_name = "Key";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (std::vector<unsigned char>, std::vector<unsigned char>),
            (KeyBytes,                   Nonce)
        );
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (std::vector<unsigned char>, std::vector<unsigned char>, SaltSignature),
            (KeyBytes,                   Nonce,                      SaltSignature)
        );
#else
        DECLARE_FIELDS(
            (std::vector<unsigned char>, std::vector<unsigned char>),
            (KeyBytes,                   EncryptedChallenge)
        );
#endif

        GETTER_SETTER(KeyBytes);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(Nonce);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(SaltSignature);
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19 */
        GETTER_SETTER(EncryptedChallenge);
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            key_bytes = ReadData<std::vector<unsigned char>>(iter, length);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            const bool has_nonce = ReadData<bool>(iter, length);
            if (has_nonce)
            {
                const int nonce_length = ReadData<VarInt>(iter, length);
                nonce = ReadByteArray(iter, length, nonce_length);
            }
            else
            {
                salt_signature = ReadData<SaltSignature>(iter, length);
            }
#else
            nonce = ReadData<std::vector<unsigned char>>(iter, length);
#endif
#else
            encrypted_challenge = ReadData<std::vector<unsigned char>>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::vector<unsigned char>>(key_bytes, container);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            WriteData<bool>(salt_signature.GetSignature().empty(), container);
            if (salt_signature.GetSignature().empty())
            {
                WriteData<VarInt>(static_cast<int>(nonce.size()), container);
                WriteByteArray(nonce, container);
            }
            else
            {
                WriteData<SaltSignature>(salt_signature, container);
            }
#else
            WriteData<std::vector<unsigned char>>(nonce, container);
#endif
#else
            WriteData<std::vector<unsigned char>>(encrypted_challenge, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["key_bytes"] = "vector of " + std::to_string(key_bytes.size()) + " unsigned char";
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            if (salt_signature.GetSignature().empty())
            {
                output["nonce"] = "vector of " + std::to_string(nonce.size()) + " unsigned char";
            }
            else
            {
                output["salt_signature"] = salt_signature;
            }
#else
            output["nonce"] = "vector of " + std::to_string(nonce.size()) + " unsigned char";
#endif
#else
            output["encrypted_challenge"] = "vector of " + std::to_string(encrypted_challenge.size()) + " unsigned char";
#endif

            return output;
        }

    private:
        std::vector<unsigned char> key_bytes;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        std::vector<unsigned char> nonce;
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SaltSignature salt_signature;
#endif
#else
        std::vector<unsigned char> encrypted_challenge;
#endif
    };
} // ProtocolCraft
