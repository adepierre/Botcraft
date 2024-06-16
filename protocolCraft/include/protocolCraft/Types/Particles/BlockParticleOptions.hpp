#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class BlockParticleOptions : public ParticleOptions
    {
        DECLARE_FIELDS(
            (VarInt),
            (State)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(State);
    };
}
