#include "botcraft/Game/Entities/entities/item/ItemEntity.hpp"

namespace Botcraft
{
    ItemEntity::ItemEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    ProtocolCraft::Slot ItemEntity::GetDataItem() const
    {
        return GetMetadata<ProtocolCraft::Slot>(BOTCRAFT_ENTITY_METADATA_INDEX("data_item"));
    }


    void ItemEntity::SetDataItem(const ProtocolCraft::Slot& data_item)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_item"), data_item);
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
