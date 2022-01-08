#include "botcraft/Game/Entities/entities/decoration/ItemFrameEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, ItemFrameEntity::metadata_count> ItemFrameEntity::metadata_names{ {
        "data_item",
        "data_rotation",
    } };

    ItemFrameEntity::ItemFrameEntity()
    {
        // Initialize all metadata with default values
        SetDataItem(ProtocolCraft::Slot());
        SetDataRotation(0);
    }

    ItemFrameEntity::~ItemFrameEntity()
    {

    }


    std::string ItemFrameEntity::GetName() const
    {
        return "ItemFrame";
    }

    EntityType ItemFrameEntity::GetType() const
    {
        return EntityType::ItemFrame;
    }

    AABB ItemFrameEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double ItemFrameEntity::GetWidth() const
    {
        return 0.5;
    }

    double ItemFrameEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string ItemFrameEntity::GetClassName()
    {
        return "ItemFrame";
    }

    EntityType ItemFrameEntity::GetClassType()
    {
        return EntityType::ItemFrame;
    }


    nlohmann::json ItemFrameEntity::Serialize() const
    {
        nlohmann::json output = HangingEntity::Serialize();

        output["metadata"]["data_item"] = GetDataItem().Serialize();
        output["metadata"]["data_rotation"] = GetDataRotation();

        return output;
    }


    void ItemFrameEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            HangingEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const ProtocolCraft::Slot& ItemFrameEntity::GetDataItem() const
    {
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_item"));
    }

    int ItemFrameEntity::GetDataRotation() const
    {
        return std::any_cast<int>(metadata.at("data_rotation"));
    }


    void ItemFrameEntity::SetDataItem(const ProtocolCraft::Slot& data_item)
    {
        metadata["data_item"] = data_item;
    }

    void ItemFrameEntity::SetDataRotation(const int data_rotation)
    {
        metadata["data_rotation"] = data_rotation;
    }

}
