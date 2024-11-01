#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffectData.hpp"
#include "protocolCraft/Types/Components/Subtypes/MobEffectInstance.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class ApplyStatusEffectsConsumeEffect : public ConsumeEffectData
        {
            SERIALIZED_FIELD(Effects, std::vector<MobEffectInstance>);
            SERIALIZED_FIELD(Probability, float);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
