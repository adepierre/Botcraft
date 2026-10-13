#include "botcraft/Game/Entities/entities/animal/equine/AbstractHorseEntity.hpp"

namespace Botcraft
{
    AbstractHorseEntity::AbstractHorseEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    char AbstractHorseEntity::GetDataIdFlags() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_flags"));
    }

#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
    std::optional<ProtocolCraft::UUID> AbstractHorseEntity::GetDataIdOwnerUuid() const
    {
        return GetMetadata<std::optional<ProtocolCraft::UUID>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_owner_uuid"));
    }
#endif


    void AbstractHorseEntity::SetDataIdFlags(const char data_id_flags)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_flags"), data_id_flags);
    }

#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
    void AbstractHorseEntity::SetDataIdOwnerUuid(const std::optional<ProtocolCraft::UUID>& data_id_owner_uuid)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_owner_uuid"), data_id_owner_uuid);
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
