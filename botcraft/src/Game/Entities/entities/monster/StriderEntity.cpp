#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/monster/StriderEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, StriderEntity::metadata_count> StriderEntity::metadata_names{ {
        "data_boost_time",
        "data_suffocating",
        "data_saddle_id",
    } };

    StriderEntity::StriderEntity()
    {
        // Initialize all metadata with default values
        SetDataBoostTime(0);
        SetDataSuffocating(false);
        SetDataSaddleId(false);
    }

    StriderEntity::~StriderEntity()
    {

    }


    std::string StriderEntity::GetName() const
    {
        return "strider";
    }

    EntityType StriderEntity::GetType() const
    {
        return EntityType::Strider;
    }


    std::string StriderEntity::GetClassName()
    {
        return "strider";
    }

    EntityType StriderEntity::GetClassType()
    {
        return EntityType::Strider;
    }


    ProtocolCraft::Json::Value StriderEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_boost_time"] = GetDataBoostTime();
        output["metadata"]["data_suffocating"] = GetDataSuffocating();
        output["metadata"]["data_saddle_id"] = GetDataSaddleId();

        return output;
    }


    void StriderEntity::SetMetadataValue(const int index, const std::any& value)
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

    int StriderEntity::GetDataBoostTime() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_boost_time"));
    }

    bool StriderEntity::GetDataSuffocating() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_suffocating"));
    }

    bool StriderEntity::GetDataSaddleId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_saddle_id"));
    }


    void StriderEntity::SetDataBoostTime(const int data_boost_time)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_boost_time"] = data_boost_time;
    }

    void StriderEntity::SetDataSuffocating(const bool data_suffocating)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_suffocating"] = data_suffocating;
    }

    void StriderEntity::SetDataSaddleId(const bool data_saddle_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_saddle_id"] = data_saddle_id;
    }


    double StriderEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double StriderEntity::GetHeightImpl() const
    {
        return 1.7;
    }

}
#endif
