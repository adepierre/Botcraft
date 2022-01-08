#if PROTOCOL_VERSION > 754
#include "botcraft/Game/Entities/entities/animal/axolotl/AxolotlEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, AxolotlEntity::metadata_count> AxolotlEntity::metadata_names{ {
        "data_variant",
        "data_playing_dead",
        "from_bucket",
    } };

    AxolotlEntity::AxolotlEntity()
    {
        // Initialize all metadata with default values
        SetDataVariant(0);
        SetDataPlayingDead(false);
        SetFromBucket(false);
    }

    AxolotlEntity::~AxolotlEntity()
    {

    }


    std::string AxolotlEntity::GetName() const
    {
        return "Axolotl";
    }

    EntityType AxolotlEntity::GetType() const
    {
        return EntityType::Axolotl;
    }

    AABB AxolotlEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double AxolotlEntity::GetWidth() const
    {
        return 0.75;
    }

    double AxolotlEntity::GetHeight() const
    {
        return 0.42;
    }


    std::string AxolotlEntity::GetClassName()
    {
        return "Axolotl";
    }

    EntityType AxolotlEntity::GetClassType()
    {
        return EntityType::Axolotl;
    }


    nlohmann::json AxolotlEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

        output["metadata"]["data_variant"] = GetDataVariant();
        output["metadata"]["data_playing_dead"] = GetDataPlayingDead();
        output["metadata"]["from_bucket"] = GetFromBucket();

        return output;
    }


    void AxolotlEntity::SetMetadataValue(const int index, const std::any& value)
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

    int AxolotlEntity::GetDataVariant() const
    {
        return std::any_cast<int>(metadata.at("data_variant"));
    }

    bool AxolotlEntity::GetDataPlayingDead() const
    {
        return std::any_cast<bool>(metadata.at("data_playing_dead"));
    }

    bool AxolotlEntity::GetFromBucket() const
    {
        return std::any_cast<bool>(metadata.at("from_bucket"));
    }


    void AxolotlEntity::SetDataVariant(const int data_variant)
    {
        metadata["data_variant"] = data_variant;
    }

    void AxolotlEntity::SetDataPlayingDead(const bool data_playing_dead)
    {
        metadata["data_playing_dead"] = data_playing_dead;
    }

    void AxolotlEntity::SetFromBucket(const bool from_bucket)
    {
        metadata["from_bucket"] = from_bucket;
    }

}
#endif
