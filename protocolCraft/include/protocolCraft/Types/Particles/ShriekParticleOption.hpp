#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

namespace ProtocolCraft
{
    class ShriekParticleOption : public ParticleOption
    {
        SERIALIZED_FIELD(Delay, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
