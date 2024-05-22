#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class DustParticleOptions : public ParticleOptions
    {
        DECLARE_FIELDS_TYPES(float, float, float, float);
        DECLARE_FIELDS_NAMES(Red, Green, Blue, Scale);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Red);
        GETTER_SETTER(Green);
        GETTER_SETTER(Blue);
        GETTER_SETTER(Scale);
    };
}
#endif
