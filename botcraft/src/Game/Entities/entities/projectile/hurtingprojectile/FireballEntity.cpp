#include "botcraft/Game/Entities/entities/projectile/hurtingprojectile/FireballEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/AssetsManager.hpp"
#endif

namespace Botcraft
{
    FireballEntity::FireballEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SetDataItemStack(ProtocolCraft::Slot());
#else
        const static int item_id = AssetsManager::getInstance().GetItemID("minecraft:fire_charge");
        ProtocolCraft::Slot default_slot;
        default_slot.SetItemId(item_id);
        default_slot.SetItemCount(1);
        SetDataItemStack(default_slot);
#endif
#endif
    }

    FireballEntity::~FireballEntity()
    {

    }

    bool FireballEntity::IsFireball() const
    {
        return true;
    }


#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    ProtocolCraft::Json::Value FireballEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractHurtingProjectileEntity::Serialize();

        output["metadata"]["data_item_stack"] = GetDataItemStack().Serialize();

        return output;
    }


    ProtocolCraft::Slot FireballEntity::GetDataItemStack() const
    {
        return GetMetadata<ProtocolCraft::Slot>(BOTCRAFT_ENTITY_METADATA_INDEX("data_item_stack"));
    }


    void FireballEntity::SetDataItemStack(const ProtocolCraft::Slot& data_item_stack)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_item_stack"), data_item_stack);
    }
#endif

}
