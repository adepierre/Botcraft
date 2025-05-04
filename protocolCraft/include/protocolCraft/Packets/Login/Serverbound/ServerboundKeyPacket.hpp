#pragma once
#include "protocolCraft/BasePacket.hpp"

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/SaltSignature.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundKeyPacket : public BasePacket<ServerboundKeyPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Key";

        SERIALIZED_FIELD(KeyBytes, std::vector<unsigned char>);
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD(Nonce, std::vector<unsigned char>);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DEFINE_CONDITION(IsHasNonceOn, GetHasNonce());
        DEFINE_CONDITION(HasSaltSignature, !GetHasNonce());

        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(HasNonce, bool);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Nonce, Internal::Conditioned<std::vector<unsigned char>, &THIS::IsHasNonceOn>);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(SaltSignature, Internal::Conditioned<ProtocolCraft::SaltSignature, &THIS::HasSaltSignature>);
#else
        SERIALIZED_FIELD(EncryptedChallenge, std::vector<unsigned char>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
    protected:
        bool GetHasNonce() const
        {
            return HasNonce;
        }

        GETTER(Nonce);
        GETTER(SaltSignature);
    public:
        auto& SetNonce(const std::optional<std::vector<unsigned char>>& Nonce_)
        {
            Nonce = Nonce_;
            HasNonce = Nonce.has_value();
            if (Nonce.has_value())
            {
                SaltSignature = std::nullopt;
            }
            return *this;
        }

        auto& SetSaltSignature(const std::optional<ProtocolCraft::SaltSignature>& SaltSignature_)
        {
            SaltSignature = SaltSignature_;
            HasNonce = !SaltSignature.has_value();
            if (SaltSignature.has_value())
            {
                Nonce = std::nullopt;
            }
            return *this;
        }
#endif
    };
} // ProtocolCraft
