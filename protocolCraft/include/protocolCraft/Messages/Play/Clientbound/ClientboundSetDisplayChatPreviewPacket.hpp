#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDisplayChatPreviewPacket : public BaseMessage<ClientboundSetDisplayChatPreviewPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Display Chat Preview";

        DECLARE_FIELDS(
            (bool),
            (Enabled)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Enabled);
    };
} //ProtocolCraft
#endif
