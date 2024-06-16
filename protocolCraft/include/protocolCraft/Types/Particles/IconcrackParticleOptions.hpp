#if PROTOCOL_VERSION < 393 /* < 1.13 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class IconcrackParticleOptions : public ParticleOptions
    {
        DECLARE_FIELDS(
            (VarInt,    VarInt),
            (Argument1, Argument2)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Argument1);
        GETTER_SETTER(Argument2);
    };
}
#endif
