#include "botcraft/Game/Entities/entities/monster/BlazeEntity.hpp"

namespace Botcraft
{
    BlazeEntity::BlazeEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataFlagsId(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 6.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.23) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 48.0) });
    }

    BlazeEntity::~BlazeEntity()
    {

    }


    std::string BlazeEntity::GetName() const
    {
        return "blaze";
    }

    EntityType BlazeEntity::GetType() const
    {
        return EntityType::Blaze;
    }


    std::string BlazeEntity::GetClassName()
    {
        return "blaze";
    }

    EntityType BlazeEntity::GetClassType()
    {
        return EntityType::Blaze;
    }


    ProtocolCraft::Json::Value BlazeEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_flags_id"] = GetDataFlagsId();

        return output;
    }


    char BlazeEntity::GetDataFlagsId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_flags_id"));
    }


    void BlazeEntity::SetDataFlagsId(const char data_flags_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_flags_id"), data_flags_id);
    }


    double BlazeEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double BlazeEntity::GetHeightImpl() const
    {
        return 1.8;
    }

}
