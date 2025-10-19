#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

#include <array>

namespace ProtocolCraft
{
    class TrailParticleOption : public ParticleOption
    {
        SERIALIZED_FIELD(Target, std::array<double, 3>);
        SERIALIZED_FIELD(Color, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
