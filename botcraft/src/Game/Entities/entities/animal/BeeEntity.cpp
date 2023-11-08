#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
#include "botcraft/Game/Entities/entities/animal/BeeEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, BeeEntity::metadata_count> BeeEntity::metadata_names{ {
        "data_flags_id",
        "data_remaining_anger_time",
    } };

    BeeEntity::BeeEntity()
    {
        // Initialize all metadata with default values
        SetDataFlagsId(0);
        SetDataRemainingAngerTime(0);
    }

    BeeEntity::~BeeEntity()
    {

    }


    std::string BeeEntity::GetName() const
    {
        return "bee";
    }

    EntityType BeeEntity::GetType() const
    {
        return EntityType::Bee;
    }

    double BeeEntity::GetWidth() const
    {
        return 0.7;
    }

    double BeeEntity::GetHeight() const
    {
        return 0.6;
    }


    std::string BeeEntity::GetClassName()
    {
        return "bee";
    }

    EntityType BeeEntity::GetClassType()
    {
        return EntityType::Bee;
    }


    ProtocolCraft::Json::Value BeeEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_flags_id"] = GetDataFlagsId();
        output["metadata"]["data_remaining_anger_time"] = GetDataRemainingAngerTime();

        return output;
    }


    void BeeEntity::SetMetadataValue(const int index, const std::any& value)
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

    char BeeEntity::GetDataFlagsId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }

    int BeeEntity::GetDataRemainingAngerTime() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_remaining_anger_time"));
    }


    void BeeEntity::SetDataFlagsId(const char data_flags_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_flags_id"] = data_flags_id;
    }

    void BeeEntity::SetDataRemainingAngerTime(const int data_remaining_anger_time)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_remaining_anger_time"] = data_remaining_anger_time;
    }

}
#endif
