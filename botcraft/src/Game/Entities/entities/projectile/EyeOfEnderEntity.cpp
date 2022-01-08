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
        return "EyeOfEnder";
    }

    EntityType EyeOfEnderEntity::GetType() const
    {
        return EntityType::EyeOfEnder;
    }

    AABB EyeOfEnderEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
        return "EyeOfEnder";
    }

    EntityType EyeOfEnderEntity::GetClassType()
    {
        return EntityType::EyeOfEnder;
    }


#if PROTOCOL_VERSION > 404
    nlohmann::json EyeOfEnderEntity::Serialize() const
    {
        nlohmann::json output = Entity::Serialize();

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
