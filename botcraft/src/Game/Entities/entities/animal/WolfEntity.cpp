#include "botcraft/Game/Entities/entities/animal/WolfEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, WolfEntity::metadata_count> WolfEntity::metadata_names{ {
#if PROTOCOL_VERSION < 499
        "data_health_id",
#endif
        "data_interested_id",
        "data_collar_color",
#if PROTOCOL_VERSION > 578
        "data_remaining_anger_time",
#endif
    } };

    WolfEntity::WolfEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION < 499
        SetDataHealthId(1.0f);
#endif
        SetDataInterestedId(false);
        SetDataCollarColor(14);
#if PROTOCOL_VERSION > 578
        SetDataRemainingAngerTime(0);
#endif
    }

    WolfEntity::~WolfEntity()
    {

    }


    std::string WolfEntity::GetName() const
    {
        return "Wolf";
    }

    EntityType WolfEntity::GetType() const
    {
        return EntityType::Wolf;
    }

    AABB WolfEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double WolfEntity::GetWidth() const
    {
        return 0.6;
    }

    double WolfEntity::GetHeight() const
    {
        return 0.85;
    }


    std::string WolfEntity::GetClassName()
    {
        return "Wolf";
    }

    EntityType WolfEntity::GetClassType()
    {
        return EntityType::Wolf;
    }


    nlohmann::json WolfEntity::Serialize() const
    {
        nlohmann::json output = TamableAnimalEntity::Serialize();

#if PROTOCOL_VERSION < 499
        output["data_health_id"] = GetDataHealthId();
#endif
        output["data_interested_id"] = GetDataInterestedId();
        output["data_collar_color"] = GetDataCollarColor();
#if PROTOCOL_VERSION > 578
        output["data_remaining_anger_time"] = GetDataRemainingAngerTime();
#endif

        return output;
    }


    void WolfEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            TamableAnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

#if PROTOCOL_VERSION < 499
    float WolfEntity::GetDataHealthId() const
    {
        return std::any_cast<float>(metadata.at("data_health_id"));
    }
#endif

    bool WolfEntity::GetDataInterestedId() const
    {
        return std::any_cast<bool>(metadata.at("data_interested_id"));
    }

    int WolfEntity::GetDataCollarColor() const
    {
        return std::any_cast<int>(metadata.at("data_collar_color"));
    }

#if PROTOCOL_VERSION > 578
    int WolfEntity::GetDataRemainingAngerTime() const
    {
        return std::any_cast<int>(metadata.at("data_remaining_anger_time"));
    }
#endif


#if PROTOCOL_VERSION < 499
    void WolfEntity::SetDataHealthId(const float data_health_id)
    {
        metadata["data_health_id"] = data_health_id;
    }
#endif

    void WolfEntity::SetDataInterestedId(const bool data_interested_id)
    {
        metadata["data_interested_id"] = data_interested_id;
    }

    void WolfEntity::SetDataCollarColor(const int data_collar_color)
    {
        metadata["data_collar_color"] = data_collar_color;
    }

#if PROTOCOL_VERSION > 578
    void WolfEntity::SetDataRemainingAngerTime(const int data_remaining_anger_time)
    {
        metadata["data_remaining_anger_time"] = data_remaining_anger_time;
    }
#endif

}
