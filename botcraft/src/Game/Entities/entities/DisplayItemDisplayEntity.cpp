#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "botcraft/Game/Entities/entities/DisplayItemDisplayEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, DisplayItemDisplayEntity::metadata_count> DisplayItemDisplayEntity::metadata_names{ {
        "data_item_stack_id",
        "data_item_display_id",
    } };

    DisplayItemDisplayEntity::DisplayItemDisplayEntity()
    {
        // Initialize all metadata with default values
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

    double DisplayItemDisplayEntity::GetWidth() const
    {
        return 0.0;
    }

    double DisplayItemDisplayEntity::GetHeight() const
    {
        return 0.0;
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


    void DisplayItemDisplayEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            DisplayEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    
    ProtocolCraft::Slot DisplayItemDisplayEntity::GetDataItemStackId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<ProtocolCraft::Slot>(metadata.at("data_item_stack_id"));
    }
    
    char DisplayItemDisplayEntity::GetDataItemDisplayId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_item_display_id"));
    }
    
    
    void DisplayItemDisplayEntity::SetDataItemStackId(const ProtocolCraft::Slot& data_item_stack_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_item_stack_id"] = data_item_stack_id;
    }
    
    void DisplayItemDisplayEntity::SetDataItemDisplayId(const char data_item_display_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_item_display_id"] = data_item_display_id;
    }
    

}
#endif
