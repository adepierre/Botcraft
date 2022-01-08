#include "botcraft/Game/Entities/entities/AgeableMobEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, AgeableMobEntity::metadata_count> AgeableMobEntity::metadata_names{ {
        "data_baby_id",
    } };

    AgeableMobEntity::AgeableMobEntity()
    {
        // Initialize all metadata with default values
        SetDataBabyId(false);
    }

    AgeableMobEntity::~AgeableMobEntity()
    {

    }

    bool AgeableMobEntity::IsAgeableMob() const
    {
        return true;
    }


    nlohmann::json AgeableMobEntity::Serialize() const
    {
        nlohmann::json output = PathfinderMobEntity::Serialize();

        output["data_baby_id"] = GetDataBabyId();

        return output;
    }


    void AgeableMobEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            PathfinderMobEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool AgeableMobEntity::GetDataBabyId() const
    {
        return std::any_cast<bool>(metadata.at("data_baby_id"));
    }


    void AgeableMobEntity::SetDataBabyId(const bool data_baby_id)
    {
        metadata["data_baby_id"] = data_baby_id;
    }

}
