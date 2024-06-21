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
            SetKeyBytes(ReadData<std::vector<unsigned char>>(iter, length));
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            const bool has_nonce = ReadData<bool>(iter, length);
            if (has_nonce)
            {
                const int nonce_length = ReadData<VarInt>(iter, length);
                SetNonce(ReadByteArray(iter, length, nonce_length));
            }
            else
            {
                SetSaltSignature(ReadData<SaltSignature>(iter, length));
            }
#else
            SetNonce(ReadData<std::vector<unsigned char>>(iter, length));
#endif
#else
            SetEncryptedChallenge(ReadData<std::vector<unsigned char>>(iter, length));
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::vector<unsigned char>>(GetKeyBytes(), container);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            WriteData<bool>(GetSaltSignature().GetSignature().empty(), container);
            if (GetSaltSignature().GetSignature().empty())
            {
                WriteData<VarInt>(static_cast<int>(GetNonce().size()), container);
                WriteByteArray(GetNonce(), container);
            }
            else
            {
                WriteData<SaltSignature>(GetSaltSignature(), container);
            }
#else
            WriteData<std::vector<unsigned char>>(GetNonce(), container);
#endif
#else
            WriteData<std::vector<unsigned char>>(GetEncryptedChallenge(), container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::KeyBytes)])] = "Vector of " + std::to_string(GetKeyBytes().size()) + " unsigned char";
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            if (GetSaltSignature().GetSignature().empty())
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Nonce)])] = "Vector of " + std::to_string(GetNonce().size()) + " unsigned char";
            }
            else
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::SaltSignature)])] = GetSaltSignature();
            }
#else
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Nonce)])] = "Vector of " + std::to_string(GetNonce().size()) + " unsigned char";
#endif
#else
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::EncryptedChallenge)])] = "Vector of " + std::to_string(GetEncryptedChallenge().size()) + " unsigned char";
#endif

            return output;
        }
    };
} // ProtocolCraft
