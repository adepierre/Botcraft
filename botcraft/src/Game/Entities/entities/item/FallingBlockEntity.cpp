#include "botcraft/Game/Entities/entities/item/FallingBlockEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, FallingBlockEntity::metadata_count> FallingBlockEntity::metadata_names{ {
        "data_start_pos",
    } };

    FallingBlockEntity::FallingBlockEntity()
    {
        // Initialize all metadata with default values
        SetDataStartPos(Position(0, 0, 0));
    }

    FallingBlockEntity::~FallingBlockEntity()
    {

    }


    std::string FallingBlockEntity::GetName() const
    {
        return "FallingBlockEntity";
    }

    EntityType FallingBlockEntity::GetType() const
    {
        return EntityType::FallingBlockEntity;
    }

    double FallingBlockEntity::GetWidth() const
    {
        return 0.98;
    }

    double FallingBlockEntity::GetHeight() const
    {
        return 0.98;
    }


    std::string FallingBlockEntity::GetClassName()
    {
        return "FallingBlockEntity";
    }

    EntityType FallingBlockEntity::GetClassType()
    {
        return EntityType::FallingBlockEntity;
    }


    nlohmann::json FallingBlockEntity::Serialize() const
    {
        nlohmann::json output = Entity::Serialize();

        output["metadata"]["data_start_pos"] = GetDataStartPos().Serialize();

        return output;
    }


    void FallingBlockEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const Position& FallingBlockEntity::GetDataStartPos() const
    {
        return std::any_cast<const Position&>(metadata.at("data_start_pos"));
    }


    void FallingBlockEntity::SetDataStartPos(const Position& data_start_pos)
    {
        metadata["data_start_pos"] = data_start_pos;
    }

}
