#if PROTOCOL_VERSION > 758
#include "botcraft/Game/Entities/entities/animal/allay/AllayEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION > 759
    const std::array<std::string, AllayEntity::metadata_count> AllayEntity::metadata_names{ {
        "data_dancing",
        "data_can_duplicate",
    } };
#endif
    AllayEntity::AllayEntity()
    {
#if PROTOCOL_VERSION > 759
        // Initialize all metadata with default values
        SetDataDancing(true);
        SetDataCanDuplicate(true);
#endif
    }

    AllayEntity::~AllayEntity()
    {

    }


    std::string AllayEntity::GetName() const
    {
        return "allay";
    }

    EntityType AllayEntity::GetType() const
    {
        return EntityType::Allay;
    }

    double AllayEntity::GetWidth() const
    {
        return 0.35;
    }

    double AllayEntity::GetHeight() const
    {
        return 0.6;
    }


    std::string AllayEntity::GetClassName()
    {
        return "allay";
    }

    EntityType AllayEntity::GetClassType()
    {
        return EntityType::Allay;
    }


#if PROTOCOL_VERSION > 759
    ProtocolCraft::Json::Value AllayEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = PathfinderMobEntity::Serialize();

        output["metadata"]["data_dancing"] = GetDataDancing();
        output["metadata"]["data_can_duplicate"] = GetDataCanDuplicate();

        return output;
    }


    void AllayEntity::SetMetadataValue(const int index, const std::any& value)
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

    bool AllayEntity::GetDataDancing() const
    {
        return std::any_cast<bool>(metadata.at("data_dancing"));
    }

    bool AllayEntity::GetDataCanDuplicate() const
    {
        return std::any_cast<bool>(metadata.at("data_can_duplicate"));
    }


    void AllayEntity::SetDataDancing(const bool data_dancing)
    {
        metadata["data_dancing"] = data_dancing;
    }

    void AllayEntity::SetDataCanDuplicate(const bool data_can_duplicate)
    {
        metadata["data_can_duplicate"] = data_can_duplicate;
    }
#endif

}
#endif
