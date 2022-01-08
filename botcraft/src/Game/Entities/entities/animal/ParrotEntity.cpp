#include "botcraft/Game/Entities/entities/animal/ParrotEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, ParrotEntity::metadata_count> ParrotEntity::metadata_names{ {
        "data_variant_id",
    } };

    ParrotEntity::ParrotEntity()
    {
        // Initialize all metadata with default values
        SetDataVariantId(0);
    }

    ParrotEntity::~ParrotEntity()
    {

    }


    std::string ParrotEntity::GetName() const
    {
        return "Parrot";
    }

    EntityType ParrotEntity::GetType() const
    {
        return EntityType::Parrot;
    }

    AABB ParrotEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double ParrotEntity::GetWidth() const
    {
        return 0.5;
    }

    double ParrotEntity::GetHeight() const
    {
        return 0.9;
    }


    std::string ParrotEntity::GetClassName()
    {
        return "Parrot";
    }

    EntityType ParrotEntity::GetClassType()
    {
        return EntityType::Parrot;
    }


    nlohmann::json ParrotEntity::Serialize() const
    {
        nlohmann::json output = ShoulderRidingEntity::Serialize();

        output["data_variant_id"] = GetDataVariantId();

        return output;
    }


    void ParrotEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            ShoulderRidingEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int ParrotEntity::GetDataVariantId() const
    {
        return std::any_cast<int>(metadata.at("data_variant_id"));
    }


    void ParrotEntity::SetDataVariantId(const int data_variant_id)
    {
        metadata["data_variant_id"] = data_variant_id;
    }

}
