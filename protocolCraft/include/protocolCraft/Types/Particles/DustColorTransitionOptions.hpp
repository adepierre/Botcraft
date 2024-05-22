#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class DustColorTransitionOptions : public ParticleOptions
    {
        DECLARE_FIELDS_TYPES(float,   float,     float,    float, float, float,   float);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS_NAMES(FromRed, FromGreen, FromBlue, Scale, ToRed, ToGreen, ToBlue);
#else
        DECLARE_FIELDS_NAMES(FromRed, FromGreen, FromBlue, ToRed, ToGreen, ToBlue, Scale);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(FromRed);
        GETTER_SETTER(FromGreen);
        GETTER_SETTER(FromBlue);
        GETTER_SETTER(Scale);
        GETTER_SETTER(ToRed);
        GETTER_SETTER(ToGreen);
        GETTER_SETTER(ToBlue);
    };
}
#endif
