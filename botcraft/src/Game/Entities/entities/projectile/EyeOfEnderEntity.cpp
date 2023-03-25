#include "botcraft/Game/Entities/entities/projectile/EyeOfEnderEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION > 404
    const std::array<std::string, EyeOfEnderEntity::metadata_count> EyeOfEnderEntity::metadata_names{ {
        "data_item_stack",
    } };
#endif

    EyeOfEnderEntity::EyeOfEnderEntity()
    {
#if PROTOCOL_VERSION > 404
        // Initialize all metadata with default values
        SetDataItemStack(ProtocolCraft::Slot());
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

    double EyeOfEnderEntity::GetWidth() const
    {
        return 0.25;
    }

    double EyeOfEnderEntity::GetHeight() const
    {
        return 0.25;
    }


    std::string EyeOfEnderEntity::GetClassName()
    {
        return "eye_of_ender";
    }

    EntityType EyeOfEnderEntity::GetClassType()
    {
        return EntityType::EyeOfEnder;
    }


#if PROTOCOL_VERSION > 404
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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const ProtocolCraft::Slot& EyeOfEnderEntity::GetDataItemStack() const
    {
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_item_stack"));
    }


    void EyeOfEnderEntity::SetDataItemStack(const ProtocolCraft::Slot& data_item_stack)
    {
        metadata["data_item_stack"] = data_item_stack;
    }
#endif

}
