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

    AABB BlazeEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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


    nlohmann::json BlazeEntity::Serialize() const
    {
        nlohmann::json output = MonsterEntity::Serialize();

        output["data_flags_id"] = GetDataFlagsId();

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
