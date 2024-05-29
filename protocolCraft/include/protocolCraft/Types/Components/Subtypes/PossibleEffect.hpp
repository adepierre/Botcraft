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
            DECLARE_FIELDS_TYPES(MobEffectInstance, float);
            DECLARE_FIELDS_NAMES(Effect,            Probability);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Effect);
            GETTER_SETTER(Probability);
        };
    }
}
#endif
