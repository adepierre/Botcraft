#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffect.hpp"

#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ApplyStatusEffectsConsumeEffect.hpp"
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ClearAllStatusEffectsConsumeEffect.hpp"
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/PlaySoundConsumeEffect.hpp"
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/RemoveStatusEffectsConsumeEffect.hpp"
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/TeleportRandomlyConsumeEffect.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        DEFINE_NETWORK_TYPE(ApplyStatusEffectsConsumeEffect);
        DEFINE_NETWORK_TYPE(ClearAllStatusEffectsConsumeEffect);
        DEFINE_NETWORK_TYPE(PlaySoundConsumeEffect);
        DEFINE_NETWORK_TYPE(RemoveStatusEffectsConsumeEffect);
        DEFINE_NETWORK_TYPE(TeleportRandomlyConsumeEffect);

        std::shared_ptr<ConsumeEffectData> ConsumeEffect::CreateConsumeEffectData(const ConsumeEffectDataType type)
        {
            switch (type)
            {
            case ConsumeEffectDataType::ApplyEffects:
                return std::make_shared<ApplyStatusEffectsConsumeEffect>();
            case ConsumeEffectDataType::ClearAllEffects:
                return std::make_shared<ClearAllStatusEffectsConsumeEffect>();
            case ConsumeEffectDataType::PlaySound:
                return std::make_shared<PlaySoundConsumeEffect>();
            case ConsumeEffectDataType::RemoveEffects:
                return std::make_shared<RemoveStatusEffectsConsumeEffect>();
            case ConsumeEffectDataType::TeleportRandomly:
                return std::make_shared<TeleportRandomlyConsumeEffect>();
            default:
                // This should not happen
                throw std::runtime_error("Unable to create ConsumeEffectData with id: " + std::to_string(static_cast<int>(type)) + ".");
                return nullptr;
            }
        }

        DEFINE_NETWORK_TYPE(ConsumeEffect);
    }
}
#endif
