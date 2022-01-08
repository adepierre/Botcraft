#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/animal/TropicalFishEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, TropicalFishEntity::metadata_count> TropicalFishEntity::metadata_names{ {
        "data_id_type_variant",
    } };

    TropicalFishEntity::TropicalFishEntity()
    {
        // Initialize all metadata with default values
        SetDataIdTypeVariant(0);
    }

    TropicalFishEntity::~TropicalFishEntity()
    {

    }


    std::string TropicalFishEntity::GetName() const
    {
        return "TropicalFish";
    }

    EntityType TropicalFishEntity::GetType() const
    {
        return EntityType::TropicalFish;
    }

    AABB TropicalFishEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double TropicalFishEntity::GetWidth() const
    {
        return 0.5;
    }

    double TropicalFishEntity::GetHeight() const
    {
        return 0.4;
    }


    std::string TropicalFishEntity::GetClassName()
    {
        return "TropicalFish";
    }

    EntityType TropicalFishEntity::GetClassType()
    {
        return EntityType::TropicalFish;
    }


    nlohmann::json TropicalFishEntity::Serialize() const
    {
        nlohmann::json output = AbstractSchoolingFishEntity::Serialize();

        output["metadata"]["data_id_type_variant"] = GetDataIdTypeVariant();

        return output;
    }


    void TropicalFishEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractSchoolingFishEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int TropicalFishEntity::GetDataIdTypeVariant() const
    {
        return std::any_cast<int>(metadata.at("data_id_type_variant"));
    }


    void TropicalFishEntity::SetDataIdTypeVariant(const int data_id_type_variant)
    {
        metadata["data_id_type_variant"] = data_id_type_variant;
    }

}
#endif
