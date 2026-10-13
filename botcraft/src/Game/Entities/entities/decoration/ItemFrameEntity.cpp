#include "botcraft/Game/Entities/entities/decoration/ItemFrameEntity.hpp"

namespace Botcraft
{
    ItemFrameEntity::ItemFrameEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    ProtocolCraft::Slot ItemFrameEntity::GetDataItem() const
    {
        return GetMetadata<ProtocolCraft::Slot>(BOTCRAFT_ENTITY_METADATA_INDEX("data_item"));
    }

    int ItemFrameEntity::GetDataRotation() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_rotation"));
    }


    void ItemFrameEntity::SetDataItem(const ProtocolCraft::Slot& data_item)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_item"), data_item);
    }

    void ItemFrameEntity::SetDataRotation(const int data_rotation)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_rotation"), data_rotation);
    }


    double ItemFrameEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double ItemFrameEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
