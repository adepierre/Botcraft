#include "botcraft/Game/Entities/entities/projectile/FireworkRocketEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, FireworkRocketEntity::metadata_count> FireworkRocketEntity::metadata_names{ {
        "data_id_fireworks_item",
        "data_attached_to_target",
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        "data_shot_at_angle",
#endif
    } };

    FireworkRocketEntity::FireworkRocketEntity()
    {
        // Initialize all metadata with default values
        SetDataIdFireworksItem(ProtocolCraft::Slot());
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
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
        return "firework_rocket";
    }

    EntityType FireworkRocketEntity::GetType() const
    {
        return EntityType::FireworkRocketEntity;
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
        return "firework_rocket";
    }

    EntityType FireworkRocketEntity::GetClassType()
    {
        return EntityType::FireworkRocketEntity;
    }


    ProtocolCraft::Json::Value FireworkRocketEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        ProtocolCraft::Json::Value output = ProjectileEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = Entity::Serialize();
#endif

        output["metadata"]["data_id_fireworks_item"] = GetDataIdFireworksItem().Serialize();
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        output["metadata"]["data_attached_to_target"] = GetDataAttachedToTarget() ? ProtocolCraft::Json::Value(GetDataAttachedToTarget().value()) : ProtocolCraft::Json::Value();
        output["metadata"]["data_shot_at_angle"] = GetDataShotAtAngle();
#else
        output["metadata"]["data_attached_to_target"] = GetDataAttachedToTarget();
#endif

        return output;
    }


    void FireworkRocketEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
            ProjectileEntity::SetMetadataValue(index, value);
#else
            Entity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const ProtocolCraft::Slot& FireworkRocketEntity::GetDataIdFireworksItem() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_id_fireworks_item"));
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    const std::optional<int>& FireworkRocketEntity::GetDataAttachedToTarget() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const std::optional<int>&>(metadata.at("data_attached_to_target"));
    }

    bool FireworkRocketEntity::GetDataShotAtAngle() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_shot_at_angle"));
    }
#else
    int FireworkRocketEntity::GetDataAttachedToTarget() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_attached_to_target"));
    }
#endif


    void FireworkRocketEntity::SetDataIdFireworksItem(const ProtocolCraft::Slot& data_id_fireworks_item)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_fireworks_item"] = data_id_fireworks_item;
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    void FireworkRocketEntity::SetDataAttachedToTarget(const std::optional<int>& data_attached_to_target)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_attached_to_target"] = data_attached_to_target;
    }

    void FireworkRocketEntity::SetDataShotAtAngle(const bool data_shot_at_angle)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_shot_at_angle"] = data_shot_at_angle;
    }
#else
    void FireworkRocketEntity::SetDataAttachedToTarget(const int data_attached_to_target)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_attached_to_target"] = data_attached_to_target;
    }
#endif

}
