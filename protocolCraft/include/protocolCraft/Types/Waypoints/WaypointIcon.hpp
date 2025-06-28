#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/Identifier.hpp"

#include <array>
#include <optional>

namespace ProtocolCraft
{
    class WaypointIcon : public NetworkType
    {
        SERIALIZED_FIELD(Style, Identifier);
        SERIALIZED_FIELD(Color, std::optional<std::array<unsigned char, 3>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
