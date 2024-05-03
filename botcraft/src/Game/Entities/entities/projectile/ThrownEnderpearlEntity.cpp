#include "botcraft/Game/Entities/entities/projectile/ThrownEnderpearlEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/AssetsManager.hpp"
#endif

namespace Botcraft
{
    ThrownEnderpearlEntity::ThrownEnderpearlEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        static const int item_id = AssetsManager::getInstance().GetItemID("minecraft:ender_pearl");
        ProtocolCraft::Slot default_slot;
        default_slot.SetItemID(item_id);
        default_slot.SetItemCount(1);
        SetDataItemStack(default_slot);
#endif
    }

    ThrownEnderpearlEntity::~ThrownEnderpearlEntity()
    {

    }


    std::string ThrownEnderpearlEntity::GetName() const
    {
        return "ender_pearl";
    }

    EntityType ThrownEnderpearlEntity::GetType() const
    {
        return EntityType::ThrownEnderpearl;
    }


    std::string ThrownEnderpearlEntity::GetClassName()
    {
        return "ender_pearl";
    }

    EntityType ThrownEnderpearlEntity::GetClassType()
    {
        return EntityType::ThrownEnderpearl;
    }


    double ThrownEnderpearlEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double ThrownEnderpearlEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
