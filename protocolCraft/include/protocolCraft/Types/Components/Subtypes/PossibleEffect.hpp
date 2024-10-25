#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/MobEffectInstance.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class PossibleEffect : public NetworkType
        {
            SERIALIZED_FIELD(Effect, MobEffectInstance);
            SERIALIZED_FIELD(Probability, float);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
