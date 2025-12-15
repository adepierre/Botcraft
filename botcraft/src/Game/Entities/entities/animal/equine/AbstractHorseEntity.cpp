#include "botcraft/Game/Entities/entities/animal/equine/AbstractHorseEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, AbstractHorseEntity::metadata_count> AbstractHorseEntity::metadata_names{ {
        "data_id_flags",
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        "data_id_owner_uuid",
#endif
    } };

    AbstractHorseEntity::AbstractHorseEntity()
    {
        // Initialize all metadata with default values
        SetDataIdFlags(0);
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        SetDataIdOwnerUuid(std::optional<ProtocolCraft::UUID>());
#endif

        // Initialize all attributes with default values
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        attributes.insert({ EntityAttribute::Type::HorseJumpStrength, EntityAttribute(EntityAttribute::Type::HorseJumpStrength, 0.7) });
#else
        attributes.insert({ EntityAttribute::Type::JumpStrength, EntityAttribute(EntityAttribute::Type::JumpStrength, 0.7) });
#endif
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 53.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.225) });
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 1.0) });
        attributes.insert({ EntityAttribute::Type::SafeFallDistance, EntityAttribute(EntityAttribute::Type::SafeFallDistance, 6.0) });
        attributes.insert({ EntityAttribute::Type::FallDamageMultiplier, EntityAttribute(EntityAttribute::Type::FallDamageMultiplier, 0.5) });
#endif
    }

    AbstractHorseEntity::~AbstractHorseEntity()
    {

    }

    bool AbstractHorseEntity::IsAbstractHorse() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractHorseEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_id_flags"] = GetDataIdFlags();
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        output["metadata"]["data_id_owner_uuid"] = GetDataIdOwnerUuid() ? ProtocolCraft::Json::Value(GetDataIdOwnerUuid().value()) : ProtocolCraft::Json::Value();
#endif

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        output["attributes"]["horse.jump_strength"] = GetAttributeJumpStrengthValue();
#endif


        return output;
    }


    void AbstractHorseEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char AbstractHorseEntity::GetDataIdFlags() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_id_flags"));
    }

#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
    std::optional<ProtocolCraft::UUID> AbstractHorseEntity::GetDataIdOwnerUuid() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<std::optional<ProtocolCraft::UUID>>(metadata.at("data_id_owner_uuid"));
    }
#endif


    void AbstractHorseEntity::SetDataIdFlags(const char data_id_flags)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_flags"] = data_id_flags;
    }

#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
    void AbstractHorseEntity::SetDataIdOwnerUuid(const std::optional<ProtocolCraft::UUID>& data_id_owner_uuid)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_owner_uuid"] = data_id_owner_uuid;
    }
#endif


#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    double AbstractHorseEntity::GetAttributeJumpStrengthValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::HorseJumpStrength).GetValue();
    }
#endif

}
