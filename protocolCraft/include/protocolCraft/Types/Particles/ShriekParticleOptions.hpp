#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class ShriekParticleOptions : public ParticleOptions
    {
        SERIALIZED_FIELD(Delay, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
