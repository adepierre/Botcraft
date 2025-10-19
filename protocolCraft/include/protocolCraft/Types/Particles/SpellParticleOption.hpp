#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

namespace ProtocolCraft
{
    class SpellParticleOption : public ParticleOption
    {
        SERIALIZED_FIELD(Color, int);
        SERIALIZED_FIELD(Power, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
