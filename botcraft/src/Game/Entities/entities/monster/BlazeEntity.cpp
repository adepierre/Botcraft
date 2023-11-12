#include "botcraft/Game/Entities/entities/monster/BlazeEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, BlazeEntity::metadata_count> BlazeEntity::metadata_names{ {
        "data_flags_id",
    } };

    BlazeEntity::BlazeEntity()
    {
        // Initialize all metadata with default values
        SetDataFlagsId(0);
    }

    BlazeEntity::~BlazeEntity()
    {

    }


    std::string BlazeEntity::GetName() const
    {
        return "blaze";
    }

    EntityType BlazeEntity::GetType() const
    {
        return EntityType::Blaze;
    }


    std::string BlazeEntity::GetClassName()
    {
        return "blaze";
    }

    EntityType BlazeEntity::GetClassType()
    {
        return EntityType::Blaze;
    }


    ProtocolCraft::Json::Value BlazeEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_flags_id"] = GetDataFlagsId();

        return output;
    }


    void BlazeEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char BlazeEntity::GetDataFlagsId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }


    void BlazeEntity::SetDataFlagsId(const char data_flags_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_flags_id"] = data_flags_id;
    }


    double BlazeEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double BlazeEntity::GetHeightImpl() const
    {
        return 1.8;
    }

}
