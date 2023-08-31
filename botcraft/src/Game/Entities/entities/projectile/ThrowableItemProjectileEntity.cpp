#include "botcraft/Game/Entities/entities/projectile/ThrowableItemProjectileEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    const std::array<std::string, ThrowableItemProjectileEntity::metadata_count> ThrowableItemProjectileEntity::metadata_names{ {
        "data_item_stack",
    } };
#endif

    ThrowableItemProjectileEntity::ThrowableItemProjectileEntity()
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        // Initialize all metadata with default values
        SetDataItemStack(ProtocolCraft::Slot());
#endif
    }

    ThrowableItemProjectileEntity::~ThrowableItemProjectileEntity()
    {

    }

    bool ThrowableItemProjectileEntity::IsThrowableItemProjectile() const
    {
        return true;
    }


#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    ProtocolCraft::Json::Value ThrowableItemProjectileEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = ThrowableProjectileEntity::Serialize();

        output["metadata"]["data_item_stack"] = GetDataItemStack().Serialize();

        return output;
    }


    void ThrowableItemProjectileEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            ThrowableProjectileEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const ProtocolCraft::Slot& ThrowableItemProjectileEntity::GetDataItemStack() const
    {
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_item_stack"));
    }


    void ThrowableItemProjectileEntity::SetDataItemStack(const ProtocolCraft::Slot& data_item_stack)
    {
        metadata["data_item_stack"] = data_item_stack;
    }
#endif

}
