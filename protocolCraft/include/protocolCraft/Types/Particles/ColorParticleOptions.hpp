#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class ColorParticleOptions : public ParticleOptions
    {
        SERIALIZED_FIELD(Color, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
