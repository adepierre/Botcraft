#include "botcraft/Game/Entities/entities/item/ItemEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, ItemEntity::metadata_count> ItemEntity::metadata_names{ {
        "data_item",
    } };

    ItemEntity::ItemEntity()
    {
        // Initialize all metadata with default values
        SetDataItem(ProtocolCraft::Slot());
    }

    ItemEntity::~ItemEntity()
    {

    }


    std::string ItemEntity::GetName() const
    {
        return "item";
    }

    EntityType ItemEntity::GetType() const
    {
        return EntityType::ItemEntity;
    }

    double ItemEntity::GetWidth() const
    {
        return 0.25;
    }

    double ItemEntity::GetHeight() const
    {
        return 0.25;
    }


    std::string ItemEntity::GetClassName()
    {
        return "item";
    }

    EntityType ItemEntity::GetClassType()
    {
        return EntityType::ItemEntity;
    }


    ProtocolCraft::Json::Value ItemEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_item"] = GetDataItem().Serialize();

        return output;
    }


    void ItemEntity::SetMetadataValue(const int index, const std::any& value)
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

    const ProtocolCraft::Slot& ItemEntity::GetDataItem() const
    {
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_item"));
    }


    void ItemEntity::SetDataItem(const ProtocolCraft::Slot& data_item)
    {
        metadata["data_item"] = data_item;
    }

}
