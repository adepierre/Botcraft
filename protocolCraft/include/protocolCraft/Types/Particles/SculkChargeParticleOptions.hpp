#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class SculkChargeParticleOptions : public ParticleOptions
    {
        DECLARE_FIELDS(
            (float),
            (Roll)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Roll);
    };
}
#endif
