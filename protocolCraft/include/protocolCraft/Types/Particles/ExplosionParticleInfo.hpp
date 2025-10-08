#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class ExplosionParticleInfo : public NetworkType
    {
        SERIALIZED_FIELD(Particle, ProtocolCraft::Particle);
        SERIALIZED_FIELD(Scaling, float);
        SERIALIZED_FIELD(Speed, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
