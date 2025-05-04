#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDisplayChatPreviewPacket : public BasePacket<ClientboundSetDisplayChatPreviewPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Display Chat Preview";

        SERIALIZED_FIELD(Enabled, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
