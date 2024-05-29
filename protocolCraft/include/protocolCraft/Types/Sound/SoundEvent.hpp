#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once


#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class SoundEvent : public NetworkType
    {
        DECLARE_FIELDS_TYPES(Identifier, std::optional<float>);
        DECLARE_FIELDS_NAMES(Location,   Range);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Location);
        GETTER_SETTER(Range);
    };
} // ProtocolCraft
#endif
