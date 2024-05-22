#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class ColorParticleOptions : public ParticleOptions
    {
        DECLARE_FIELDS_TYPES(int);
        DECLARE_FIELDS_NAMES(Color);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Color);
    };
}
#endif
