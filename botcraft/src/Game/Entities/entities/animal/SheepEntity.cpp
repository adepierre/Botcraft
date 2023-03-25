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
        return "sheep";
    }

    EntityType SheepEntity::GetType() const
    {
        return EntityType::Sheep;
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
        return "sheep";
    }

    EntityType SheepEntity::GetClassType()
    {
        return EntityType::Sheep;
    }


    ProtocolCraft::Json::Value SheepEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

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
