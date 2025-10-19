#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include <array>
#endif

namespace ProtocolCraft
{
    class DustParticleOption : public ParticleOption
    {
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(Color, std::array<float, 3>);
#else
        SERIALIZED_FIELD(Color, int);
#endif
        SERIALIZED_FIELD(Scale, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
