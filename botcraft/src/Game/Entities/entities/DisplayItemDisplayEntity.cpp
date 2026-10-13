#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "botcraft/Game/Entities/entities/DisplayItemDisplayEntity.hpp"

namespace Botcraft
{
    DisplayItemDisplayEntity::DisplayItemDisplayEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataItemStackId(ProtocolCraft::Slot());
        SetDataItemDisplayId(0);
    }

    DisplayItemDisplayEntity::~DisplayItemDisplayEntity()
    {

    }


    std::string DisplayItemDisplayEntity::GetName() const
    {
        return "item_display";
    }

    EntityType DisplayItemDisplayEntity::GetType() const
    {
        return EntityType::DisplayItemDisplay;
    }


    std::string DisplayItemDisplayEntity::GetClassName()
    {
        return "item_display";
    }

    EntityType DisplayItemDisplayEntity::GetClassType()
    {
        return EntityType::DisplayItemDisplay;
    }



    ProtocolCraft::Json::Value DisplayItemDisplayEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = DisplayEntity::Serialize();

        output["metadata"]["data_item_stack_id"] = GetDataItemStackId().Serialize();
        output["metadata"]["data_item_display_id"] = GetDataItemDisplayId();

        return output;
    }


    ProtocolCraft::Slot DisplayItemDisplayEntity::GetDataItemStackId() const
    {
        return GetMetadata<ProtocolCraft::Slot>(BOTCRAFT_ENTITY_METADATA_INDEX("data_item_stack_id"));
    }

    char DisplayItemDisplayEntity::GetDataItemDisplayId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_item_display_id"));
    }


    void DisplayItemDisplayEntity::SetDataItemStackId(const ProtocolCraft::Slot& data_item_stack_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_item_stack_id"), data_item_stack_id);
    }

    void DisplayItemDisplayEntity::SetDataItemDisplayId(const char data_item_display_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_item_display_id"), data_item_display_id);
    }


    double DisplayItemDisplayEntity::GetWidthImpl() const
    {
        return 0.0;
    }

    double DisplayItemDisplayEntity::GetHeightImpl() const
    {
        return 0.0;
    }

}
#endif
