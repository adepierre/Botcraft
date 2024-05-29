#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/MobEffectInstance.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypePotionContents : public DataComponentType
        {
            DECLARE_FIELDS_TYPES(std::optional<VarInt>, std::optional<int>, std::vector<MobEffectInstance>);
            DECLARE_FIELDS_NAMES(PotionId,              CustomColor,        CustomEffects);
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(PotionId);
            GETTER_SETTER(CustomColor);
            GETTER_SETTER(CustomEffects);
        };
    }
}
#endif
