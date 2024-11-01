#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffect.hpp"

#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffectData.hpp"
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ApplyStatusEffectsConsumeEffect.hpp"
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ClearAllStatusEffectsConsumeEffect.hpp"
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/PlaySoundConsumeEffect.hpp"
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/RemoveStatusEffectsConsumeEffect.hpp"
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/TeleportRandomlyConsumeEffect.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        DEFINE_NETWORK_TYPE(ConsumeEffectData);
        DEFINE_NETWORK_TYPE(ApplyStatusEffectsConsumeEffect);
        DEFINE_NETWORK_TYPE(ClearAllStatusEffectsConsumeEffect);
        DEFINE_NETWORK_TYPE(PlaySoundConsumeEffect);
        DEFINE_NETWORK_TYPE(RemoveStatusEffectsConsumeEffect);
        DEFINE_NETWORK_TYPE(TeleportRandomlyConsumeEffect);

        ConsumeEffect& ConsumeEffect::SetType(const ConsumeEffectDataType type)
        {
            if (type <= ConsumeEffectDataType::None || type >= ConsumeEffectDataType::NUM_CONSUME_EFFECT_DATA_TYPES)
            {
                throw std::runtime_error("Unable to create ConsumeEffectData with id: " + std::to_string(static_cast<int>(type)) + ".");
            }
            Type = type;

            switch (Type)
            {
            case ConsumeEffectDataType::ApplyEffects:
                Data = std::make_shared<ApplyStatusEffectsConsumeEffect>();
                break;
            case ConsumeEffectDataType::ClearAllEffects:
                Data = std::make_shared<ClearAllStatusEffectsConsumeEffect>();
                break;
            case ConsumeEffectDataType::PlaySound:
                Data = std::make_shared<PlaySoundConsumeEffect>();
                break;
            case ConsumeEffectDataType::RemoveEffects:
                Data = std::make_shared<RemoveStatusEffectsConsumeEffect>();
                break;
            case ConsumeEffectDataType::TeleportRandomly:
                Data = std::make_shared<TeleportRandomlyConsumeEffect>();
                break;
            default:
                // This should not happen
                throw std::runtime_error("Unable to create ConsumeEffectData with id: " + std::to_string(static_cast<int>(Type)) + ".");
                Data = nullptr;
                break;
            }
            return *this;
        }


        void ConsumeEffect::ReadImpl(ReadIterator& iter, size_t& length)
        {
            SetType(ReadData<ConsumeEffectDataType, VarInt>(iter, length));
            if (GetData() != nullptr)
            {
                GetData()->Read(iter, length);
            }
        }

        void ConsumeEffect::WriteImpl(WriteContainer& container) const
        {
            WriteData<ConsumeEffectDataType, VarInt>(GetType(), container);
            if (GetData() != nullptr)
            {
                GetData()->Write(container);
            }
        }

        Json::Value ConsumeEffect::SerializeImpl() const
        {
            Json::Value output;

            output[std::string(field_name<Type_index>)] = GetType();
            output[std::string(field_name<Data_index>)] = GetData() == nullptr ? Json::Object() : GetData()->Serialize();

            return output;
        }
    }
}
#endif
