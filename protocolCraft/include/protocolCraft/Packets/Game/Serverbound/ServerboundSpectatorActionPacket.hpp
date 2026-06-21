#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

#include <optional>

namespace ProtocolCraft
{
    class ServerboundSpectatorActionPacket : public BasePacket<ServerboundSpectatorActionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Spectator Action";

        SERIALIZED_FIELD(SpectateEntityId, std::optional<VarInt>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
