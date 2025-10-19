#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include <array>
#endif

namespace ProtocolCraft
{
    class DustColorTransitionOption : public ParticleOption
    {
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(FromColor, std::array<float, 3>);
#else
        SERIALIZED_FIELD(FromColor, int);
#endif
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(Scale, float);
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(ToColor, std::array<float, 3>);
#else
        SERIALIZED_FIELD(ToColor, int);
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        SERIALIZED_FIELD(Scale, float);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
