#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once


#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class SoundEvent : public NetworkType
    {
        DECLARE_FIELDS(
            (Identifier, std::optional<float>),
            (Location,   Range)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Location);
        GETTER_SETTER(Range);
    };
} // ProtocolCraft
#endif
