#include "botcraft/Game/Entities/entities/ambient/BatEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, BatEntity::metadata_count> BatEntity::metadata_names{ {
        "data_id_flags",
    } };

    BatEntity::BatEntity()
    {
        // Initialize all metadata with default values
        SetDataIdFlags(0);
    }

    BatEntity::~BatEntity()
    {

    }


    std::string BatEntity::GetName() const
    {
        return "Bat";
    }

    EntityType BatEntity::GetType() const
    {
        return EntityType::Bat;
    }

    AABB BatEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double BatEntity::GetWidth() const
    {
        return 0.5;
    }

    double BatEntity::GetHeight() const
    {
        return 0.9;
    }


    std::string BatEntity::GetClassName()
    {
        return "Bat";
    }

    EntityType BatEntity::GetClassType()
    {
        return EntityType::Bat;
    }


    nlohmann::json BatEntity::Serialize() const
    {
        nlohmann::json output = AmbientCreatureEntity::Serialize();

        output["data_id_flags"] = GetDataIdFlags();

        return output;
    }


    void BatEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AmbientCreatureEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char BatEntity::GetDataIdFlags() const
    {
        return std::any_cast<char>(metadata.at("data_id_flags"));
    }


    void BatEntity::SetDataIdFlags(const char data_id_flags)
    {
        metadata["data_id_flags"] = data_id_flags;
    }

}
