#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHelloPacket : public BaseMessage<ClientboundHelloPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Hello";

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (std::string, std::vector<unsigned char>, std::vector<unsigned char>),
            (ServerId,    PublicKey,                  Nonce)
        );
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (std::string, std::vector<unsigned char>, std::vector<unsigned char>),
            (ServerId,    PublicKey,                  Challenge)
        );
#else
        DECLARE_FIELDS(
            (std::string, std::vector<unsigned char>, std::vector<unsigned char>, bool),
            (ServerId,    PublicKey,                  Challenge,                  ShouldAuthenticate)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ServerId);
        GETTER_SETTER(PublicKey);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(Nonce);
#else
        GETTER_SETTER(Challenge);
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        GETTER_SETTER(ShouldAuthenticate);
#endif
    };
}
