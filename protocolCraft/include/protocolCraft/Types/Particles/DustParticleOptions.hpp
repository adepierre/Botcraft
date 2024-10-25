#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class DustParticleOptions : public ParticleOptions
    {
        SERIALIZED_FIELD(Red, float);
        SERIALIZED_FIELD(Green, float);
        SERIALIZED_FIELD(Blue, float);
        SERIALIZED_FIELD(Scale, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
