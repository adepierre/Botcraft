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
        return "item_frame";
    }

    EntityType ItemFrameEntity::GetType() const
    {
        return EntityType::ItemFrame;
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
        return "item_frame";
    }

    EntityType ItemFrameEntity::GetClassType()
    {
        return EntityType::ItemFrame;
    }


    ProtocolCraft::Json::Value ItemFrameEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = HangingEntity::Serialize();

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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const ProtocolCraft::Slot& ItemFrameEntity::GetDataItem() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_item"));
    }

    int ItemFrameEntity::GetDataRotation() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_rotation"));
    }


    void ItemFrameEntity::SetDataItem(const ProtocolCraft::Slot& data_item)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_item"] = data_item;
    }

    void ItemFrameEntity::SetDataRotation(const int data_rotation)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_rotation"] = data_rotation;
    }

}
