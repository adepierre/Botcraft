#include "botcraft/Game/Entities/entities/item/FallingBlockEntity.hpp"

namespace Botcraft
{
    FallingBlockEntity::FallingBlockEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataStartPos(Position(0, 0, 0));
    }

    FallingBlockEntity::~FallingBlockEntity()
    {

    }


    std::string FallingBlockEntity::GetName() const
    {
        return "falling_block";
    }

    EntityType FallingBlockEntity::GetType() const
    {
        return EntityType::FallingBlockEntity;
    }


    std::string FallingBlockEntity::GetClassName()
    {
        return "falling_block";
    }

    EntityType FallingBlockEntity::GetClassType()
    {
        return EntityType::FallingBlockEntity;
    }


    ProtocolCraft::Json::Value FallingBlockEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_start_pos"] = GetDataStartPos().Serialize();

        return output;
    }


    Position FallingBlockEntity::GetDataStartPos() const
    {
        return GetMetadata<Position>(BOTCRAFT_ENTITY_METADATA_INDEX("data_start_pos"));
    }


    void FallingBlockEntity::SetDataStartPos(const Position& data_start_pos)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_start_pos"), data_start_pos);
    }


    double FallingBlockEntity::GetWidthImpl() const
    {
        return 0.98;
    }

    double FallingBlockEntity::GetHeightImpl() const
    {
        return 0.98;
    }

}
