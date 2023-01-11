#if PROTOCOL_VERSION > 760
#include "botcraft/Game/Entities/entities/animal/camel/CamelEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, CamelEntity::metadata_count> CamelEntity::metadata_names{ {
        "dash",
        "last_pose_change_tick",
    } };

    CamelEntity::CamelEntity()
    {
        // Initialize all metadata with default values
        SetDash(true);
        SetLastPoseChangeTick(-52);
    }

    CamelEntity::~CamelEntity()
    {

    }


    std::string CamelEntity::GetName() const
    {
        return "Camel";
    }

    EntityType CamelEntity::GetType() const
    {
        return EntityType::Camel;
    }

    double CamelEntity::GetWidth() const
    {
        return 1.7;
    }

    double CamelEntity::GetHeight() const
    {
        return 2.375;
    }


    std::string CamelEntity::GetClassName()
    {
        return "Camel";
    }

    EntityType CamelEntity::GetClassType()
    {
        return EntityType::Camel;
    }


    ProtocolCraft::Json::Value CamelEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractHorseEntity::Serialize();

        output["metadata"]["dash"] = GetDash();
        output["metadata"]["last_pose_change_tick"] = GetLastPoseChangeTick();

        return output;
    }


    void CamelEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractHorseEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool CamelEntity::GetDash() const
    {
        return std::any_cast<bool>(metadata.at("dash"));
    }

    long long int CamelEntity::GetLastPoseChangeTick() const
    {
        return std::any_cast<long long int>(metadata.at("last_pose_change_tick"));
    }


    void CamelEntity::SetDash(const bool dash)
    {
        metadata["dash"] = dash;
    }

    void CamelEntity::SetLastPoseChangeTick(const long long int last_pose_change_tick)
    {
        metadata["last_pose_change_tick"] = last_pose_change_tick;
    }

}
#endif
