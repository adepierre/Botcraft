#include "botcraft/Game/Entities/entities/item/ItemEntity.hpp"

#include <mutex>

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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    ProtocolCraft::Slot ItemEntity::GetDataItem() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<ProtocolCraft::Slot>(metadata.at("data_item"));
    }


    void ItemEntity::SetDataItem(const ProtocolCraft::Slot& data_item)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_item"] = data_item;
    }


    double ItemEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double ItemEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
