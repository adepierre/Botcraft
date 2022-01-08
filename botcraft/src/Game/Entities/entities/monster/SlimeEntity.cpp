#include "botcraft/Game/Entities/entities/monster/SlimeEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, SlimeEntity::metadata_count> SlimeEntity::metadata_names{ {
        "id_size",
    } };

    SlimeEntity::SlimeEntity()
    {
        // Initialize all metadata with default values
        SetIdSize(1);
    }

    SlimeEntity::~SlimeEntity()
    {

    }


    std::string SlimeEntity::GetName() const
    {
        return "Slime";
    }

    EntityType SlimeEntity::GetType() const
    {
        return EntityType::Slime;
    }

    AABB SlimeEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double SlimeEntity::GetWidth() const
    {
        return 2.04;
    }

    double SlimeEntity::GetHeight() const
    {
        return 2.04;
    }


    std::string SlimeEntity::GetClassName()
    {
        return "Slime";
    }

    EntityType SlimeEntity::GetClassType()
    {
        return EntityType::Slime;
    }


    nlohmann::json SlimeEntity::Serialize() const
    {
        nlohmann::json output = MobEntity::Serialize();

        output["metadata"]["id_size"] = GetIdSize();

        return output;
    }


    void SlimeEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MobEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int SlimeEntity::GetIdSize() const
    {
        return std::any_cast<int>(metadata.at("id_size"));
    }


    void SlimeEntity::SetIdSize(const int id_size)
    {
        metadata["id_size"] = id_size;
    }

}
