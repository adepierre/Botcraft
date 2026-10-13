#include "botcraft/Game/Entities/entities/projectile/FireworkRocketEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/AssetsManager.hpp"
#endif

namespace Botcraft
{
    FireworkRocketEntity::FireworkRocketEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SetDataIdFireworksItem(ProtocolCraft::Slot());
#else
        const static int item_id = AssetsManager::getInstance().GetItemID("minecraft:firework_rocket");
        ProtocolCraft::Slot default_slot;
        default_slot.SetItemId(item_id);
        default_slot.SetItemCount(1);
        SetDataIdFireworksItem(default_slot);
#endif
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


    ProtocolCraft::Slot FireworkRocketEntity::GetDataIdFireworksItem() const
    {
        return GetMetadata<ProtocolCraft::Slot>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_fireworks_item"));
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    std::optional<int> FireworkRocketEntity::GetDataAttachedToTarget() const
    {
        return GetMetadata<std::optional<int>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_attached_to_target"));
    }

    bool FireworkRocketEntity::GetDataShotAtAngle() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_shot_at_angle"));
    }
#else
    int FireworkRocketEntity::GetDataAttachedToTarget() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_attached_to_target"));
    }
#endif


    void FireworkRocketEntity::SetDataIdFireworksItem(const ProtocolCraft::Slot& data_id_fireworks_item)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_fireworks_item"), data_id_fireworks_item);
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    void FireworkRocketEntity::SetDataAttachedToTarget(const std::optional<int>& data_attached_to_target)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_attached_to_target"), data_attached_to_target);
    }

    void FireworkRocketEntity::SetDataShotAtAngle(const bool data_shot_at_angle)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_shot_at_angle"), data_shot_at_angle);
    }
#else
    void FireworkRocketEntity::SetDataAttachedToTarget(const int data_attached_to_target)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_attached_to_target"), data_attached_to_target);
    }
#endif


    double FireworkRocketEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double FireworkRocketEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
