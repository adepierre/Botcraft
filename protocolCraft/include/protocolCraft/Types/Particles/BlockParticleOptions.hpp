#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class BlockParticleOptions : public ParticleOptions
    {
        SERIALIZED_FIELD(State, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
