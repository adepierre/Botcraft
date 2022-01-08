#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/animal/PufferfishEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, PufferfishEntity::metadata_count> PufferfishEntity::metadata_names{ {
        "puff_state",
    } };

    PufferfishEntity::PufferfishEntity()
    {
        // Initialize all metadata with default values
        SetPuffState(0);
    }

    PufferfishEntity::~PufferfishEntity()
    {

    }


    std::string PufferfishEntity::GetName() const
    {
        return "Pufferfish";
    }

    EntityType PufferfishEntity::GetType() const
    {
        return EntityType::Pufferfish;
    }

    AABB PufferfishEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double PufferfishEntity::GetWidth() const
    {
        return 0.7;
    }

    double PufferfishEntity::GetHeight() const
    {
        return 0.7;
    }


    std::string PufferfishEntity::GetClassName()
    {
        return "Pufferfish";
    }

    EntityType PufferfishEntity::GetClassType()
    {
        return EntityType::Pufferfish;
    }


    nlohmann::json PufferfishEntity::Serialize() const
    {
        nlohmann::json output = AbstractFishEntity::Serialize();

        output["puff_state"] = GetPuffState();

        return output;
    }


    void PufferfishEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractFishEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int PufferfishEntity::GetPuffState() const
    {
        return std::any_cast<int>(metadata.at("puff_state"));
    }


    void PufferfishEntity::SetPuffState(const int puff_state)
    {
        metadata["puff_state"] = puff_state;
    }

}
#endif
