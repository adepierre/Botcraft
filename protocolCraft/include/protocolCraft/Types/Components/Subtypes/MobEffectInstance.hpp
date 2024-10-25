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
            SERIALIZED_FIELD(MobEffect, VarInt);
            SERIALIZED_FIELD(Details, MobEffectInstanceDetails);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
