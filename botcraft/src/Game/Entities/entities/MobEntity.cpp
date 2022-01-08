#include "botcraft/Game/Entities/entities/MobEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, MobEntity::metadata_count> MobEntity::metadata_names{ {
        "data_mob_flags_id",
    } };

    MobEntity::MobEntity()
    {
        // Initialize all metadata with default values
        SetDataMobFlagsId(0);
    }

    MobEntity::~MobEntity()
    {

    }

    bool MobEntity::IsMob() const
    {
        return true;
    }


    nlohmann::json MobEntity::Serialize() const
    {
        nlohmann::json output = LivingEntity::Serialize();

        output["metadata"]["data_mob_flags_id"] = GetDataMobFlagsId();

        return output;
    }


    void MobEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            LivingEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char MobEntity::GetDataMobFlagsId() const
    {
        return std::any_cast<char>(metadata.at("data_mob_flags_id"));
    }


    void MobEntity::SetDataMobFlagsId(const char data_mob_flags_id)
    {
        metadata["data_mob_flags_id"] = data_mob_flags_id;
    }

}
