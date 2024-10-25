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
            SERIALIZED_FIELD(PotionId, std::optional<VarInt>);
            SERIALIZED_FIELD(CustomColor, std::optional<int>);
            SERIALIZED_FIELD(CustomEffects, std::vector<MobEffectInstance>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
