#include "botcraft/Game/Entities/entities/projectile/throwableitemprojectile/ThrownEggEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/AssetsManager.hpp"
#endif

namespace Botcraft
{
    ThrownEggEntity::ThrownEggEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        static const int item_id = AssetsManager::getInstance().GetItemID("minecraft:egg");
        ProtocolCraft::Slot default_slot;
        default_slot.SetItemId(item_id);
        default_slot.SetItemCount(1);
        SetDataItemStack(default_slot);
#endif
    }

    ThrownEggEntity::~ThrownEggEntity()
    {

    }


    std::string ThrownEggEntity::GetName() const
    {
        return "egg";
    }

    EntityType ThrownEggEntity::GetType() const
    {
        return EntityType::ThrownEgg;
    }


    std::string ThrownEggEntity::GetClassName()
    {
        return "egg";
    }

    EntityType ThrownEggEntity::GetClassType()
    {
        return EntityType::ThrownEgg;
    }


    double ThrownEggEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double ThrownEggEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
