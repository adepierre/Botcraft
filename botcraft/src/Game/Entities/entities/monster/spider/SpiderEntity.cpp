#include "botcraft/Game/Entities/entities/monster/spider/SpiderEntity.hpp"

namespace Botcraft
{
    SpiderEntity::SpiderEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataFlagsId(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 16.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
    }

    SpiderEntity::~SpiderEntity()
    {

    }


    std::string SpiderEntity::GetName() const
    {
        return "spider";
    }

    EntityType SpiderEntity::GetType() const
    {
        return EntityType::Spider;
    }


    std::string SpiderEntity::GetClassName()
    {
        return "spider";
    }

    EntityType SpiderEntity::GetClassType()
    {
        return EntityType::Spider;
    }


    ProtocolCraft::Json::Value SpiderEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_flags_id"] = GetDataFlagsId();

        return output;
    }


    char SpiderEntity::GetDataFlagsId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_flags_id"));
    }


    void SpiderEntity::SetDataFlagsId(const char data_flags_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_flags_id"), data_flags_id);
    }


    double SpiderEntity::GetWidthImpl() const
    {
        return 1.4;
    }

    double SpiderEntity::GetHeightImpl() const
    {
        return 0.9;
    }

}
