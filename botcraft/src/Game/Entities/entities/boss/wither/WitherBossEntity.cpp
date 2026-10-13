#include "botcraft/Game/Entities/entities/boss/wither/WitherBossEntity.hpp"

namespace Botcraft
{
    WitherBossEntity::WitherBossEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataTargetA(0);
        SetDataTargetB(0);
        SetDataTargetC(0);
        SetDataIdInv(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 300.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.6) });
        attributes.insert({ EntityAttribute::Type::FlyingSpeed, EntityAttribute(EntityAttribute::Type::FlyingSpeed, 0.6) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 40.0) });
        attributes.insert({ EntityAttribute::Type::Armor, EntityAttribute(EntityAttribute::Type::Armor, 4.0) });
    }

    WitherBossEntity::~WitherBossEntity()
    {

    }


    std::string WitherBossEntity::GetName() const
    {
        return "wither";
    }

    EntityType WitherBossEntity::GetType() const
    {
        return EntityType::WitherBoss;
    }


    std::string WitherBossEntity::GetClassName()
    {
        return "wither";
    }

    EntityType WitherBossEntity::GetClassType()
    {
        return EntityType::WitherBoss;
    }


    ProtocolCraft::Json::Value WitherBossEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_target_a"] = GetDataTargetA();
        output["metadata"]["data_target_b"] = GetDataTargetB();
        output["metadata"]["data_target_c"] = GetDataTargetC();
        output["metadata"]["data_id_inv"] = GetDataIdInv();

        output["attributes"]["flying_speed"] = GetAttributeFlyingSpeedValue();

        return output;
    }


    int WitherBossEntity::GetDataTargetA() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_target_a"));
    }

    int WitherBossEntity::GetDataTargetB() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_target_b"));
    }

    int WitherBossEntity::GetDataTargetC() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_target_c"));
    }

    int WitherBossEntity::GetDataIdInv() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_inv"));
    }


    void WitherBossEntity::SetDataTargetA(const int data_target_a)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_target_a"), data_target_a);
    }

    void WitherBossEntity::SetDataTargetB(const int data_target_b)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_target_b"), data_target_b);
    }

    void WitherBossEntity::SetDataTargetC(const int data_target_c)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_target_c"), data_target_c);
    }

    void WitherBossEntity::SetDataIdInv(const int data_id_inv)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_inv"), data_id_inv);
    }


    double WitherBossEntity::GetAttributeFlyingSpeedValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::FlyingSpeed).GetValue();
    }


    double WitherBossEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double WitherBossEntity::GetHeightImpl() const
    {
        return 3.5;
    }

}
