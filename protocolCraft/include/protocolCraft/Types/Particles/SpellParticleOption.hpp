#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class SpellParticleOptions : public ParticleOptions
    {
        SERIALIZED_FIELD(Color, int);
        SERIALIZED_FIELD(Power, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
