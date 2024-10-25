#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHelloPacket : public BaseMessage<ClientboundHelloPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Hello";

        SERIALIZED_FIELD(ServerId, std::string);
        SERIALIZED_FIELD(PublicKey, std::vector<unsigned char>);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(Nonce, std::vector<unsigned char>);
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        SERIALIZED_FIELD(Challenge, std::vector<unsigned char>);
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        SERIALIZED_FIELD(ShouldAuthenticate, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
