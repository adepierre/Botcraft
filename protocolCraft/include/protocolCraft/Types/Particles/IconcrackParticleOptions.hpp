#if PROTOCOL_VERSION < 393 /* < 1.13 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class IconcrackParticleOptions : public ParticleOptions
    {
        SERIALIZED_FIELD(Argument1, VarInt);
        SERIALIZED_FIELD(Argument2, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
