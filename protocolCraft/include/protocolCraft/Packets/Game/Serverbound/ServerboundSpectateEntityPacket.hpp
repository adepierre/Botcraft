#if PROTOCOL_VERSION > 774 /* > 1.21.11 */ && PROTOCOL_VERSION < 776 /* < 26.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundSpectateEntityPacket : public BasePacket<ServerboundSpectateEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Spectate Entity";

        SERIALIZED_FIELD(EntityId, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
