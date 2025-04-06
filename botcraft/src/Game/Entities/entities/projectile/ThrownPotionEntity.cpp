#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
#include "botcraft/Game/Entities/entities/projectile/ThrownPotionEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/AssetsManager.hpp"
#endif

#if PROTOCOL_VERSION < 579 /* < 1.16 */
#include <mutex>
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 579 /* < 1.16 */
    const std::array<std::string, ThrownPotionEntity::metadata_count> ThrownPotionEntity::metadata_names{ {
        "data_item_stack",
    } };
#endif

    ThrownPotionEntity::ThrownPotionEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION < 579 /* < 1.16 */
        SetDataItemStack(ProtocolCraft::Slot());
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        static const int item_id = AssetsManager::getInstance().GetItemID("minecraft:splash_potion");
        ProtocolCraft::Slot default_slot;
        default_slot.SetItemId(item_id);
        default_slot.SetItemCount(1);
        SetDataItemStack(default_slot);
#endif
    }

    ThrownPotionEntity::~ThrownPotionEntity()
    {

    }


    std::string ThrownPotionEntity::GetName() const
    {
        return "potion";
    }

    EntityType ThrownPotionEntity::GetType() const
    {
        return EntityType::ThrownPotion;
    }


    std::string ThrownPotionEntity::GetClassName()
    {
        return "potion";
    }

    EntityType ThrownPotionEntity::GetClassType()
    {
        return EntityType::ThrownPotion;
    }


#if PROTOCOL_VERSION < 579 /* < 1.16 */
    ProtocolCraft::Json::Value ThrownPotionEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = ThrowableProjectileEntity::Serialize();

        output["metadata"]["data_item_stack"] = GetDataItemStack().Serialize();

        return output;
    }


    void ThrownPotionEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            ThrowableProjectileEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    ProtocolCraft::Slot ThrownPotionEntity::GetDataItemStack() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<ProtocolCraft::Slot>(metadata.at("data_item_stack"));
    }


    void ThrownPotionEntity::SetDataItemStack(const ProtocolCraft::Slot& data_item_stack)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_item_stack"] = data_item_stack;
    }
#endif


    double ThrownPotionEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double ThrownPotionEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
#endif
