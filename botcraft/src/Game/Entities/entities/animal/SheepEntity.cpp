#include "botcraft/Game/Entities/entities/animal/SheepEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, SheepEntity::metadata_count> SheepEntity::metadata_names{ {
        "data_wool_id",
    } };

    SheepEntity::SheepEntity()
    {
        // Initialize all metadata with default values
        SetDataWoolId(0);
    }

    SheepEntity::~SheepEntity()
    {

    }


    std::string SheepEntity::GetName() const
    {
        return "Sheep";
    }

    EntityType SheepEntity::GetType() const
    {
        return EntityType::Sheep;
    }

    AABB SheepEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double SheepEntity::GetWidth() const
    {
        return 0.9;
    }

    double SheepEntity::GetHeight() const
    {
        return 1.3;
    }


    std::string SheepEntity::GetClassName()
    {
        return "Sheep";
    }

    EntityType SheepEntity::GetClassType()
    {
        return EntityType::Sheep;
    }


    nlohmann::json SheepEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

        output["metadata"]["data_wool_id"] = GetDataWoolId();

        return output;
    }


    void SheepEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char SheepEntity::GetDataWoolId() const
    {
        return std::any_cast<char>(metadata.at("data_wool_id"));
    }


    void SheepEntity::SetDataWoolId(const char data_wool_id)
    {
        metadata["data_wool_id"] = data_wool_id;
    }

}
