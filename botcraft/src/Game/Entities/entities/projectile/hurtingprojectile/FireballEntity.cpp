#include "botcraft/Game/Entities/entities/projectile/hurtingprojectile/FireballEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/AssetsManager.hpp"
#endif

#include <mutex>

namespace Botcraft
{
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    const std::array<std::string, FireballEntity::metadata_count> FireballEntity::metadata_names{ {
        "data_item_stack",
    } };
#endif

    FireballEntity::FireballEntity()
    {
        // Initialize all metadata with default values
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


    void FireballEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractHurtingProjectileEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    ProtocolCraft::Slot FireballEntity::GetDataItemStack() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_item_stack"));
    }


    void FireballEntity::SetDataItemStack(const ProtocolCraft::Slot& data_item_stack)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_item_stack"] = data_item_stack;
    }
#endif

}
