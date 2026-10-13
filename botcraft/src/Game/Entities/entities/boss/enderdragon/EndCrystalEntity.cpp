#include "botcraft/Game/Entities/entities/boss/enderdragon/EndCrystalEntity.hpp"

namespace Botcraft
{
    EndCrystalEntity::EndCrystalEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataBeamTarget(std::optional<Position>());
        SetDataShowBottom(true);
    }

    EndCrystalEntity::~EndCrystalEntity()
    {

    }


    std::string EndCrystalEntity::GetName() const
    {
        return "end_crystal";
    }

    EntityType EndCrystalEntity::GetType() const
    {
        return EntityType::EndCrystal;
    }


    std::string EndCrystalEntity::GetClassName()
    {
        return "end_crystal";
    }

    EntityType EndCrystalEntity::GetClassType()
    {
        return EntityType::EndCrystal;
    }


    ProtocolCraft::Json::Value EndCrystalEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_beam_target"] = GetDataBeamTarget() ? GetDataBeamTarget().value().Serialize() : ProtocolCraft::Json::Value();
        output["metadata"]["data_show_bottom"] = GetDataShowBottom();

        return output;
    }


    std::optional<Position> EndCrystalEntity::GetDataBeamTarget() const
    {
        return GetMetadata<std::optional<Position>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_beam_target"));
    }

    bool EndCrystalEntity::GetDataShowBottom() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_show_bottom"));
    }


    void EndCrystalEntity::SetDataBeamTarget(const std::optional<Position>& data_beam_target)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_beam_target"), data_beam_target);
    }

    void EndCrystalEntity::SetDataShowBottom(const bool data_show_bottom)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_show_bottom"), data_show_bottom);
    }


    double EndCrystalEntity::GetWidthImpl() const
    {
        return 2.0;
    }

    double EndCrystalEntity::GetHeightImpl() const
    {
        return 2.0;
    }

}
