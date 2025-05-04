#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/SignedMessageHeader.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerChatHeaderPacket : public BasePacket<ClientboundPlayerChatHeaderPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Chat Header";

        SERIALIZED_FIELD(Header, SignedMessageHeader);
        SERIALIZED_FIELD(HeaderSignature, std::vector<unsigned char>);
        SERIALIZED_FIELD(BodyDigest, std::vector<unsigned char>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
