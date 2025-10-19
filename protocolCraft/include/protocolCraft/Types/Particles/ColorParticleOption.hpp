#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

namespace ProtocolCraft
{
    class ColorParticleOption : public ParticleOption
    {
        SERIALIZED_FIELD(Color, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
