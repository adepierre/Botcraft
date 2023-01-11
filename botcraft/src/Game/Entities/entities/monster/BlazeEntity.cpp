#include "botcraft/Game/Entities/entities/monster/BlazeEntity.hpp"

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
        return "Blaze";
    }

    EntityType BlazeEntity::GetType() const
    {
        return EntityType::Blaze;
    }

    double BlazeEntity::GetWidth() const
    {
        return 0.6;
    }

    double BlazeEntity::GetHeight() const
    {
        return 1.8;
    }


    std::string BlazeEntity::GetClassName()
    {
        return "Blaze";
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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char BlazeEntity::GetDataFlagsId() const
    {
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }


    void BlazeEntity::SetDataFlagsId(const char data_flags_id)
    {
        metadata["data_flags_id"] = data_flags_id;
    }

}
