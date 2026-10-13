#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "botcraft/Game/Entities/entities/animal/frog/FrogEntity.hpp"

namespace Botcraft
{
    FrogEntity::FrogEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataVariantId(0);
        SetDataTongueTargetId(std::optional<int>());

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 1.0) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 10.0) });
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 1.0) });
#endif
    }

    FrogEntity::~FrogEntity()
    {

    }


    std::string FrogEntity::GetName() const
    {
        return "frog";
    }

    EntityType FrogEntity::GetType() const
    {
        return EntityType::Frog;
    }


    std::string FrogEntity::GetClassName()
    {
        return "frog";
    }

    EntityType FrogEntity::GetClassType()
    {
        return EntityType::Frog;
    }


    ProtocolCraft::Json::Value FrogEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_variant_id"] = GetDataVariantId();
        output["metadata"]["data_tongue_target_id"] = GetDataTongueTargetId() ? ProtocolCraft::Json::Value(GetDataTongueTargetId().value()) : ProtocolCraft::Json::Value();

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


    int FrogEntity::GetDataVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"));
    }

    std::optional<int> FrogEntity::GetDataTongueTargetId() const
    {
        return GetMetadata<std::optional<int>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_tongue_target_id"));
    }


    void FrogEntity::SetDataVariantId(const int data_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"), data_variant_id);
    }

    void FrogEntity::SetDataTongueTargetId(const std::optional<int>& data_tongue_target_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_tongue_target_id"), data_tongue_target_id);
    }


    double FrogEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }


    double FrogEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double FrogEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
#endif
