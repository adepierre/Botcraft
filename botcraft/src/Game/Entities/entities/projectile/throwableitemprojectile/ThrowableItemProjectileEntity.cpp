#include "botcraft/Game/Entities/entities/projectile/throwableitemprojectile/ThrowableItemProjectileEntity.hpp"

namespace Botcraft
{
    ThrowableItemProjectileEntity::ThrowableItemProjectileEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
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


    ProtocolCraft::Slot ThrowableItemProjectileEntity::GetDataItemStack() const
    {
        return GetMetadata<ProtocolCraft::Slot>(BOTCRAFT_ENTITY_METADATA_INDEX("data_item_stack"));
    }


    void ThrowableItemProjectileEntity::SetDataItemStack(const ProtocolCraft::Slot& data_item_stack)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_item_stack"), data_item_stack);
    }
#endif

}
