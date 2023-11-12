#include "botcraft/Game/Entities/entities/animal/PigEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, PigEntity::metadata_count> PigEntity::metadata_names{ {
        "data_saddle_id",
        "data_boost_time",
    } };

    PigEntity::PigEntity()
    {
        // Initialize all metadata with default values
        SetDataSaddleId(false);
        SetDataBoostTime(0);
    }

    PigEntity::~PigEntity()
    {

    }


    std::string PigEntity::GetName() const
    {
        return "pig";
    }

    EntityType PigEntity::GetType() const
    {
        return EntityType::Pig;
    }


    std::string PigEntity::GetClassName()
    {
        return "pig";
    }

    EntityType PigEntity::GetClassType()
    {
        return EntityType::Pig;
    }


    ProtocolCraft::Json::Value PigEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_saddle_id"] = GetDataSaddleId();
        output["metadata"]["data_boost_time"] = GetDataBoostTime();

        return output;
    }


    void PigEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool PigEntity::GetDataSaddleId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_saddle_id"));
    }

    int PigEntity::GetDataBoostTime() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_boost_time"));
    }


    void PigEntity::SetDataSaddleId(const bool data_saddle_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_saddle_id"] = data_saddle_id;
    }

    void PigEntity::SetDataBoostTime(const int data_boost_time)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_boost_time"] = data_boost_time;
    }


    double PigEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double PigEntity::GetHeightImpl() const
    {
        return 0.9;
    }

}
