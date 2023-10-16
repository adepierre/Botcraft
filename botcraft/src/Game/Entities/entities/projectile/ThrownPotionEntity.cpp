#include "botcraft/Game/Entities/entities/projectile/ThrownPotionEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION < 579 /* < 1.16 */
    const std::array<std::string, ThrownPotionEntity::metadata_count> ThrownPotionEntity::metadata_names{ {
        "data_item_stack",
    } };
#endif

    ThrownPotionEntity::ThrownPotionEntity()
    {
#if PROTOCOL_VERSION < 579 /* < 1.16 */
        // Initialize all metadata with default values
        SetDataItemStack(ProtocolCraft::Slot());
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

    double ThrownPotionEntity::GetWidth() const
    {
        return 0.25;
    }

    double ThrownPotionEntity::GetHeight() const
    {
        return 0.25;
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

    const ProtocolCraft::Slot& ThrownPotionEntity::GetDataItemStack() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_item_stack"));
    }


    void ThrownPotionEntity::SetDataItemStack(const ProtocolCraft::Slot& data_item_stack)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_item_stack"] = data_item_stack;
    }
#endif

}
