#include "botcraft/Game/Entities/entities/monster/GuardianEntity.hpp"

namespace Botcraft
{
    GuardianEntity::GuardianEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataIdMoving(false);
        SetDataIdAttackTarget(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 6.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.5) });
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 16.0) });
#endif
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 30.0) });
    }

    GuardianEntity::~GuardianEntity()
    {

    }


    std::string GuardianEntity::GetName() const
    {
        return "guardian";
    }

    EntityType GuardianEntity::GetType() const
    {
        return EntityType::Guardian;
    }


    std::string GuardianEntity::GetClassName()
    {
        return "guardian";
    }

    EntityType GuardianEntity::GetClassType()
    {
        return EntityType::Guardian;
    }


    ProtocolCraft::Json::Value GuardianEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_id_moving"] = GetDataIdMoving();
        output["metadata"]["data_id_attack_target"] = GetDataIdAttackTarget();

        return output;
    }


    bool GuardianEntity::GetDataIdMoving() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_moving"));
    }

    int GuardianEntity::GetDataIdAttackTarget() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_attack_target"));
    }


    void GuardianEntity::SetDataIdMoving(const bool data_id_moving)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_moving"), data_id_moving);
    }

    void GuardianEntity::SetDataIdAttackTarget(const int data_id_attack_target)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_attack_target"), data_id_attack_target);
    }


    double GuardianEntity::GetWidthImpl() const
    {
        return 0.85;
    }

    double GuardianEntity::GetHeightImpl() const
    {
        return 0.85;
    }

}
