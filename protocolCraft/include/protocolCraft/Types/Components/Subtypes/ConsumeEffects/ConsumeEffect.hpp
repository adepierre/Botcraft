#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

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
            SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Type, Internal::DiffType<ConsumeEffectDataType, VarInt>);
            SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Data, std::shared_ptr<ConsumeEffectData>);

            DECLARE_READ_WRITE_SERIALIZE;

            GETTER(Type);
            GETTER(Data);

        public:
            ConsumeEffect& SetType(const ConsumeEffectDataType type);
        };
    }
}
#endif
