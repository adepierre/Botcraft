#include "botcraft/Game/Entities/entities/projectile/FireballEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    const std::array<std::string, FireballEntity::metadata_count> FireballEntity::metadata_names{ {
        "data_item_stack",
    } };
#endif

    FireballEntity::FireballEntity()
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        // Initialize all metadata with default values
        SetDataItemStack(ProtocolCraft::Slot());
#endif
    }

    FireballEntity::~FireballEntity()
    {

    }

    bool FireballEntity::IsFireball() const
    {
        return true;
    }


#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    ProtocolCraft::Json::Value FireballEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractHurtingProjectileEntity::Serialize();

        output["metadata"]["data_item_stack"] = GetDataItemStack().Serialize();

        return output;
    }


    void FireballEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractHurtingProjectileEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    ProtocolCraft::Slot FireballEntity::GetDataItemStack() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_item_stack"));
    }


    void FireballEntity::SetDataItemStack(const ProtocolCraft::Slot& data_item_stack)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_item_stack"] = data_item_stack;
    }
#endif

}
