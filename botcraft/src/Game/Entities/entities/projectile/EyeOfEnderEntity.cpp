#include "botcraft/Game/Entities/entities/projectile/EyeOfEnderEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/AssetsManager.hpp"
#endif

namespace Botcraft
{
    EyeOfEnderEntity::EyeOfEnderEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SetDataItemStack(ProtocolCraft::Slot());
#else
        const static int item_id = AssetsManager::getInstance().GetItemID("minecraft:ender_eye");
        ProtocolCraft::Slot default_slot;
        default_slot.SetItemId(item_id);
        default_slot.SetItemCount(1);
        SetDataItemStack(default_slot);
#endif
#endif
    }

    EyeOfEnderEntity::~EyeOfEnderEntity()
    {

    }


    std::string EyeOfEnderEntity::GetName() const
    {
        return "eye_of_ender";
    }

    EntityType EyeOfEnderEntity::GetType() const
    {
        return EntityType::EyeOfEnder;
    }


    std::string EyeOfEnderEntity::GetClassName()
    {
        return "eye_of_ender";
    }

    EntityType EyeOfEnderEntity::GetClassType()
    {
        return EntityType::EyeOfEnder;
    }


#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    ProtocolCraft::Json::Value EyeOfEnderEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_item_stack"] = GetDataItemStack().Serialize();

        return output;
    }


    ProtocolCraft::Slot EyeOfEnderEntity::GetDataItemStack() const
    {
        return GetMetadata<ProtocolCraft::Slot>(BOTCRAFT_ENTITY_METADATA_INDEX("data_item_stack"));
    }


    void EyeOfEnderEntity::SetDataItemStack(const ProtocolCraft::Slot& data_item_stack)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_item_stack"), data_item_stack);
    }
#endif


    double EyeOfEnderEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double EyeOfEnderEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
