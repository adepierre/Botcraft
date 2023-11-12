#include "botcraft/Game/Entities/entities/boss/enderdragon/EndCrystalEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, EndCrystalEntity::metadata_count> EndCrystalEntity::metadata_names{ {
        "data_beam_target",
        "data_show_bottom",
    } };

    EndCrystalEntity::EndCrystalEntity()
    {
        // Initialize all metadata with default values
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


    void EndCrystalEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    std::optional<Position> EndCrystalEntity::GetDataBeamTarget() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<std::optional<Position>>(metadata.at("data_beam_target"));
    }

    bool EndCrystalEntity::GetDataShowBottom() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_show_bottom"));
    }


    void EndCrystalEntity::SetDataBeamTarget(const std::optional<Position>& data_beam_target)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_beam_target"] = data_beam_target;
    }

    void EndCrystalEntity::SetDataShowBottom(const bool data_show_bottom)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_show_bottom"] = data_show_bottom;
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
