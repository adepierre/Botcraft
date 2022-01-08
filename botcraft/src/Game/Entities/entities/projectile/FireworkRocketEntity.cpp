#include "botcraft/Game/Entities/entities/projectile/FireworkRocketEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, FireworkRocketEntity::metadata_count> FireworkRocketEntity::metadata_names{ {
        "data_id_fireworks_item",
        "data_attached_to_target",
#if PROTOCOL_VERSION > 404
        "data_shot_at_angle",
#endif
    } };

    FireworkRocketEntity::FireworkRocketEntity()
    {
        // Initialize all metadata with default values
        SetDataIdFireworksItem(ProtocolCraft::Slot());
#if PROTOCOL_VERSION > 404
        SetDataAttachedToTarget(std::optional<int>());
        SetDataShotAtAngle(false);
#else
        SetDataAttachedToTarget(0);
#endif
    }

    FireworkRocketEntity::~FireworkRocketEntity()
    {

    }


    std::string FireworkRocketEntity::GetName() const
    {
        return "FireworkRocketEntity";
    }

    EntityType FireworkRocketEntity::GetType() const
    {
        return EntityType::FireworkRocketEntity;
    }

    AABB FireworkRocketEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double FireworkRocketEntity::GetWidth() const
    {
        return 0.25;
    }

    double FireworkRocketEntity::GetHeight() const
    {
        return 0.25;
    }


    std::string FireworkRocketEntity::GetClassName()
    {
        return "FireworkRocketEntity";
    }

    EntityType FireworkRocketEntity::GetClassType()
    {
        return EntityType::FireworkRocketEntity;
    }


    nlohmann::json FireworkRocketEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 578
        nlohmann::json output = ProjectileEntity::Serialize();
#else
        nlohmann::json output = Entity::Serialize();
#endif

        output["data_id_fireworks_item"] = GetDataIdFireworksItem().Serialize();
#if PROTOCOL_VERSION > 404
        output["data_attached_to_target"] = GetDataAttachedToTarget() ? nlohmann::json(GetDataAttachedToTarget().value()) : nullptr;
        output["data_shot_at_angle"] = GetDataShotAtAngle();
#else
        output["data_attached_to_target"] = GetDataAttachedToTarget();
#endif

        return output;
    }


    void FireworkRocketEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION > 578
            ProjectileEntity::SetMetadataValue(index, value);
#else
            Entity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const ProtocolCraft::Slot& FireworkRocketEntity::GetDataIdFireworksItem() const
    {
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_id_fireworks_item"));
    }

#if PROTOCOL_VERSION > 404
    const std::optional<int>& FireworkRocketEntity::GetDataAttachedToTarget() const
    {
        return std::any_cast<const std::optional<int>&>(metadata.at("data_attached_to_target"));
    }

    bool FireworkRocketEntity::GetDataShotAtAngle() const
    {
        return std::any_cast<bool>(metadata.at("data_shot_at_angle"));
    }
#else
    int FireworkRocketEntity::GetDataAttachedToTarget() const
    {
        return std::any_cast<int>(metadata.at("data_attached_to_target"));
    }
#endif


    void FireworkRocketEntity::SetDataIdFireworksItem(const ProtocolCraft::Slot& data_id_fireworks_item)
    {
        metadata["data_id_fireworks_item"] = data_id_fireworks_item;
    }

#if PROTOCOL_VERSION > 404
    void FireworkRocketEntity::SetDataAttachedToTarget(const std::optional<int>& data_attached_to_target)
    {
        metadata["data_attached_to_target"] = data_attached_to_target;
    }

    void FireworkRocketEntity::SetDataShotAtAngle(const bool data_shot_at_angle)
    {
        metadata["data_shot_at_angle"] = data_shot_at_angle;
    }
#else
    void FireworkRocketEntity::SetDataAttachedToTarget(const int data_attached_to_target)
    {
        metadata["data_attached_to_target"] = data_attached_to_target;
    }
#endif

}
