#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once


#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class SoundEvent : public NetworkType
    {
        SERIALIZED_FIELD(Location, Identifier);
        SERIALIZED_FIELD(Range, std::optional<float>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
