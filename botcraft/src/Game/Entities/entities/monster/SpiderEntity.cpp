#include "botcraft/Game/Entities/entities/monster/SpiderEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, SpiderEntity::metadata_count> SpiderEntity::metadata_names{ {
        "data_flags_id",
    } };

    SpiderEntity::SpiderEntity()
    {
        // Initialize all metadata with default values
        SetDataFlagsId(0);
    }

    SpiderEntity::~SpiderEntity()
    {

    }


    std::string SpiderEntity::GetName() const
    {
        return "Spider";
    }

    EntityType SpiderEntity::GetType() const
    {
        return EntityType::Spider;
    }

    AABB SpiderEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double SpiderEntity::GetWidth() const
    {
        return 1.4;
    }

    double SpiderEntity::GetHeight() const
    {
        return 0.9;
    }


    std::string SpiderEntity::GetClassName()
    {
        return "Spider";
    }

    EntityType SpiderEntity::GetClassType()
    {
        return EntityType::Spider;
    }


    nlohmann::json SpiderEntity::Serialize() const
    {
        nlohmann::json output = MonsterEntity::Serialize();

        output["data_flags_id"] = GetDataFlagsId();

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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char SpiderEntity::GetDataFlagsId() const
    {
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }


    void SpiderEntity::SetDataFlagsId(const char data_flags_id)
    {
        metadata["data_flags_id"] = data_flags_id;
    }

}
