#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundSetSubtitleTextPacket : public BaseMessage<ClientboundSetSubtitleTextPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set subtitle Text";

        DECLARE_FIELDS(
            (Chat),
            (Text)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Text);
    };
} //ProtocolCraft
#endif
