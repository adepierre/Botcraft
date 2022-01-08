#include "botcraft/Game/Entities/entities/animal/SnowGolemEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, SnowGolemEntity::metadata_count> SnowGolemEntity::metadata_names{ {
        "data_pumpkin_id",
    } };

    SnowGolemEntity::SnowGolemEntity()
    {
        // Initialize all metadata with default values
        SetDataPumpkinId(16);
    }

    SnowGolemEntity::~SnowGolemEntity()
    {

    }


    std::string SnowGolemEntity::GetName() const
    {
        return "SnowGolem";
    }

    EntityType SnowGolemEntity::GetType() const
    {
        return EntityType::SnowGolem;
    }

    AABB SnowGolemEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double SnowGolemEntity::GetWidth() const
    {
        return 0.7;
    }

    double SnowGolemEntity::GetHeight() const
    {
        return 1.9;
    }


    std::string SnowGolemEntity::GetClassName()
    {
        return "SnowGolem";
    }

    EntityType SnowGolemEntity::GetClassType()
    {
        return EntityType::SnowGolem;
    }


    nlohmann::json SnowGolemEntity::Serialize() const
    {
        nlohmann::json output = AbstractGolemEntity::Serialize();

        output["metadata"]["data_pumpkin_id"] = GetDataPumpkinId();

        return output;
    }


    void SnowGolemEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractGolemEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char SnowGolemEntity::GetDataPumpkinId() const
    {
        return std::any_cast<char>(metadata.at("data_pumpkin_id"));
    }


    void SnowGolemEntity::SetDataPumpkinId(const char data_pumpkin_id)
    {
        metadata["data_pumpkin_id"] = data_pumpkin_id;
    }

}
