#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

namespace ProtocolCraft
{
    class EmptyParticleOption : public ParticleOption
    {
        DECLARE_READ_WRITE_SERIALIZE;
    };
}
