#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class DustColorTransitionOptions : public ParticleOptions
    {
        SERIALIZED_FIELD(FromRed, float);
        SERIALIZED_FIELD(FromGreen, float);
        SERIALIZED_FIELD(FromBlue, float);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(Scale, float);
#endif
        SERIALIZED_FIELD(ToRed, float);
        SERIALIZED_FIELD(ToGreen, float);
        SERIALIZED_FIELD(ToBlue, float);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        SERIALIZED_FIELD(Scale, float);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
