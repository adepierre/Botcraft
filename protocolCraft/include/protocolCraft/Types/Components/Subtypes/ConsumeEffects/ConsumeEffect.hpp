#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Utilities/DynamicType.hpp"

#include <memory>

namespace ProtocolCraft
{
    namespace Components
    {
        enum class ConsumeEffectDataType
        {
            None = -1,
            ApplyEffects,
            RemoveEffects,
            ClearAllEffects,
            TeleportRandomly,
            PlaySound,
            NUM_CONSUME_EFFECT_DATA_TYPES
        };

        class ConsumeEffectData;

        class ConsumeEffect : public NetworkType
        {
        private:
            static std::shared_ptr<ConsumeEffectData> CreateConsumeEffectData(const ConsumeEffectDataType type);

            SERIALIZED_DYNAMIC_FIELD(ConsumeEffect, Type, Data, ConsumeEffectData, ConsumeEffect::CreateConsumeEffectData, Internal::DiffType<ConsumeEffectDataType, VarInt>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
