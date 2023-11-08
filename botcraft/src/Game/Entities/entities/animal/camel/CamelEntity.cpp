#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
#include "botcraft/Game/Entities/entities/animal/camel/CamelEntity.hpp"

#include <mutex>

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
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        SetLastPoseChangeTick(-52);
#else
        SetLastPoseChangeTick(0);
#endif
    }

    CamelEntity::~CamelEntity()
    {

    }


    std::string CamelEntity::GetName() const
    {
        return "camel";
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
        return "camel";
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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool CamelEntity::GetDash() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("dash"));
    }

    long long int CamelEntity::GetLastPoseChangeTick() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<long long int>(metadata.at("last_pose_change_tick"));
    }


    void CamelEntity::SetDash(const bool dash)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["dash"] = dash;
    }

    void CamelEntity::SetLastPoseChangeTick(const long long int last_pose_change_tick)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["last_pose_change_tick"] = last_pose_change_tick;
    }

}
#endif
