#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class ShriekParticleOptions : public ParticleOptions
    {
        DECLARE_FIELDS(
            (VarInt),
            (Delay)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Delay);
    };
}
#endif
