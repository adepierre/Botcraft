#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

namespace ProtocolCraft
{
    class BlockParticleOption : public ParticleOption
    {
        SERIALIZED_FIELD(State, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
