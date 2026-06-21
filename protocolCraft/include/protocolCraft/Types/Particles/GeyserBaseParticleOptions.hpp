#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

namespace ProtocolCraft
{
    class GeyserBaseParticleOptions : public ParticleOption
    {
        SERIALIZED_FIELD(WaterBlocks, int);
        SERIALIZED_FIELD(BurstImpulseBase, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
