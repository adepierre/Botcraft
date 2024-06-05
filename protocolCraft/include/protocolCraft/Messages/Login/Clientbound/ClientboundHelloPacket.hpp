#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHelloPacket : public BaseMessage<ClientboundHelloPacket>
    {
    public:
        static constexpr int packet_id = 0x01;
        static constexpr std::string_view packet_name = "Hello";

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS_TYPES(std::string, std::vector<unsigned char>, std::vector<unsigned char>);
        DECLARE_FIELDS_NAMES(ServerId,    PublicKey,                  Nonce);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS_TYPES(std::string, std::vector<unsigned char>, std::vector<unsigned char>);
        DECLARE_FIELDS_NAMES(ServerId,    PublicKey,                  Challenge);
#else
        DECLARE_FIELDS_TYPES(std::string, std::vector<unsigned char>, std::vector<unsigned char>, bool);
        DECLARE_FIELDS_NAMES(ServerId,    PublicKey,                  Challenge,                  ShouldAuthenticate);
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
