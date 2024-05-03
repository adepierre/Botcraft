#include "botcraft/Game/Entities/entities/projectile/EyeOfEnderEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/AssetsManager.hpp"
#endif

#include <mutex>

namespace Botcraft
{
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    const std::array<std::string, EyeOfEnderEntity::metadata_count> EyeOfEnderEntity::metadata_names{ {
        "data_item_stack",
    } };
#endif

    EyeOfEnderEntity::EyeOfEnderEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SetDataItemStack(ProtocolCraft::Slot());
#else
        const static int item_id = AssetsManager::getInstance().GetItemID("minecraft:ender_eye");
        ProtocolCraft::Slot default_slot;
        default_slot.SetItemID(item_id);
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


    void EyeOfEnderEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    ProtocolCraft::Slot EyeOfEnderEntity::GetDataItemStack() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<ProtocolCraft::Slot>(metadata.at("data_item_stack"));
    }


    void EyeOfEnderEntity::SetDataItemStack(const ProtocolCraft::Slot& data_item_stack)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_item_stack"] = data_item_stack;
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
