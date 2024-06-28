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
        DECLARE_CONDITION(HasNonce, GetHasNonce());
        DECLARE_CONDITION(HasSaltSignature, !GetHasNonce());

        DECLARE_FIELDS(
            (std::vector<unsigned char>, bool,     Internal::Conditioned<std::vector<unsigned char>, &THIS::HasNonce>, Internal::Conditioned<SaltSignature, &THIS::HasSaltSignature>),
            (KeyBytes,                   HasNonce, Nonce,                                                              SaltSignature)
        );
#else
        DECLARE_FIELDS(
            (std::vector<unsigned char>, std::vector<unsigned char>),
            (KeyBytes,                   EncryptedChallenge)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(KeyBytes);
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        GETTER_SETTER(Nonce);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
    protected:
        bool GetHasNonce() const
        {
            return std::get<static_cast<size_t>(FieldsEnum::HasNonce)>(fields);
        }

        GETTER(Nonce);
        GETTER(SaltSignature);
    public:
        auto& SetNonce(const std::optional<std::vector<unsigned char>>& Nonce)
        {
            std::get<static_cast<size_t>(FieldsEnum::Nonce)>(fields) = Nonce;
            std::get<static_cast<size_t>(FieldsEnum::HasNonce)>(fields) = Nonce.has_value();
            if (Nonce.has_value())
            {
                std::get<static_cast<size_t>(FieldsEnum::SaltSignature)>(fields) = std::nullopt;
            }
            return *this;
        }

        auto& SetSaltSignature(const std::optional<SaltSignature>& SaltSignature)
        {
            std::get<static_cast<size_t>(FieldsEnum::SaltSignature)>(fields) = SaltSignature;
            std::get<static_cast<size_t>(FieldsEnum::HasNonce)>(fields) = !SaltSignature.has_value();
            if (SaltSignature.has_value())
            {
                std::get<static_cast<size_t>(FieldsEnum::Nonce)>(fields) = std::nullopt;
            }
            return *this;
        }
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        GETTER_SETTER(EncryptedChallenge);
#endif
    };
} // ProtocolCraft
