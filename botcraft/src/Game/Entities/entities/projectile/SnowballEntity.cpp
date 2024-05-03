#include "botcraft/Game/Entities/entities/projectile/SnowballEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/AssetsManager.hpp"
#endif

namespace Botcraft
{
    SnowballEntity::SnowballEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        static const int item_id = AssetsManager::getInstance().GetItemID("minecraft:snowball");
        ProtocolCraft::Slot default_slot;
        default_slot.SetItemID(item_id);
        default_slot.SetItemCount(1);
        SetDataItemStack(default_slot);
#endif
    }

    SnowballEntity::~SnowballEntity()
    {

    }


    std::string SnowballEntity::GetName() const
    {
        return "snowball";
    }

    EntityType SnowballEntity::GetType() const
    {
        return EntityType::Snowball;
    }


    std::string SnowballEntity::GetClassName()
    {
        return "snowball";
    }

    EntityType SnowballEntity::GetClassType()
    {
        return EntityType::Snowball;
    }


    double SnowballEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double SnowballEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
