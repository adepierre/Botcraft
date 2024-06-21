#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/SignedMessageHeader.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerChatHeaderPacket : public BaseMessage<ClientboundPlayerChatHeaderPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Player Chat Header";

        DECLARE_FIELDS(
            (SignedMessageHeader, std::vector<unsigned char>, std::vector<unsigned char>),
            (Header,              HeaderSignature,            BodyDigest)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Header);
        GETTER_SETTER(HeaderSignature);
        GETTER_SETTER(BodyDigest);
    };
}
#endif
