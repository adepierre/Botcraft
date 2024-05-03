#include "botcraft/Game/Entities/entities/projectile/ThrownExperienceBottleEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/AssetsManager.hpp"
#endif

namespace Botcraft
{
    ThrownExperienceBottleEntity::ThrownExperienceBottleEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        static const int item_id = AssetsManager::getInstance().GetItemID("minecraft:experience_bottle");
        ProtocolCraft::Slot default_slot;
        default_slot.SetItemID(item_id);
        default_slot.SetItemCount(1);
        SetDataItemStack(default_slot);
#endif
    }

    ThrownExperienceBottleEntity::~ThrownExperienceBottleEntity()
    {

    }


    std::string ThrownExperienceBottleEntity::GetName() const
    {
        return "experience_bottle";
    }

    EntityType ThrownExperienceBottleEntity::GetType() const
    {
        return EntityType::ThrownExperienceBottle;
    }


    std::string ThrownExperienceBottleEntity::GetClassName()
    {
        return "experience_bottle";
    }

    EntityType ThrownExperienceBottleEntity::GetClassType()
    {
        return EntityType::ThrownExperienceBottle;
    }


    double ThrownExperienceBottleEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double ThrownExperienceBottleEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
