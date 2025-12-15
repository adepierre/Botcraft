#include "botcraft/Game/Entities/entities/monster/spider/SpiderEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, SpiderEntity::metadata_count> SpiderEntity::metadata_names{ {
        "data_flags_id",
    } };

    SpiderEntity::SpiderEntity()
    {
        // Initialize all metadata with default values
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


    void SpiderEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char SpiderEntity::GetDataFlagsId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }


    void SpiderEntity::SetDataFlagsId(const char data_flags_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_flags_id"] = data_flags_id;
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
