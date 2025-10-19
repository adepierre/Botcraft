#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

namespace ProtocolCraft
{
    class SculkChargeParticleOption : public ParticleOption
    {
        SERIALIZED_FIELD(Roll, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
