#if PROTOCOL_VERSION > 498
#include "botcraft/Game/Entities/entities/animal/BeeEntity.hpp"

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
        return "Bee";
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
        return "Bee";
    }

    EntityType BeeEntity::GetClassType()
    {
        return EntityType::Bee;
    }


    nlohmann::json BeeEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char BeeEntity::GetDataFlagsId() const
    {
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }

    int BeeEntity::GetDataRemainingAngerTime() const
    {
        return std::any_cast<int>(metadata.at("data_remaining_anger_time"));
    }


    void BeeEntity::SetDataFlagsId(const char data_flags_id)
    {
        metadata["data_flags_id"] = data_flags_id;
    }

    void BeeEntity::SetDataRemainingAngerTime(const int data_remaining_anger_time)
    {
        metadata["data_remaining_anger_time"] = data_remaining_anger_time;
    }

}
#endif
