#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/MobEffectInstanceDetails.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class MobEffectInstance : public NetworkType
        {
            DECLARE_FIELDS(
                (VarInt,    MobEffectInstanceDetails),
                (MobEffect, Details)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(MobEffect);
            GETTER_SETTER(Details);
        };
    }
}
#endif
