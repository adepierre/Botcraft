#include "botcraft/Game/Entities/entities/projectile/FireballEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION > 404
    const std::array<std::string, FireballEntity::metadata_count> FireballEntity::metadata_names{ {
        "data_item_stack",
    } };
#endif

    FireballEntity::FireballEntity()
    {
#if PROTOCOL_VERSION > 404
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


#if PROTOCOL_VERSION > 404
    nlohmann::json FireballEntity::Serialize() const
    {
        nlohmann::json output = AbstractHurtingProjectileEntity::Serialize();

        output["data_item_stack"] = GetDataItemStack().Serialize();

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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const ProtocolCraft::Slot& FireballEntity::GetDataItemStack() const
    {
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_item_stack"));
    }


    void FireballEntity::SetDataItemStack(const ProtocolCraft::Slot& data_item_stack)
    {
        metadata["data_item_stack"] = data_item_stack;
    }
#endif

}
