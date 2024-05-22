#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class BlockParticleOptions : public ParticleOptions
    {
        DECLARE_FIELDS_TYPES(VarInt);
        DECLARE_FIELDS_NAMES(State);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(State);
    };
}
