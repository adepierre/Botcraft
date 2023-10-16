#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "botcraft/Game/Entities/entities/DisplayTextDisplayEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, DisplayTextDisplayEntity::metadata_count> DisplayTextDisplayEntity::metadata_names{ {
        "data_text_id",
        "data_line_width_id",
        "data_background_color_id",
        "data_text_opacity_id",
        "data_style_flags_id",
    } };

    DisplayTextDisplayEntity::DisplayTextDisplayEntity()
    {
        // Initialize all metadata with default values
        SetDataTextId(ProtocolCraft::Chat());
        SetDataLineWidthId(200);
        SetDataBackgroundColorId(0x40000000);
        SetDataTextOpacityId(-1);
        SetDataStyleFlagsId(0);
    }

    DisplayTextDisplayEntity::~DisplayTextDisplayEntity()
    {

    }


    std::string DisplayTextDisplayEntity::GetName() const
    {
        return "text_display";
    }

    EntityType DisplayTextDisplayEntity::GetType() const
    {
        return EntityType::DisplayTextDisplay;
    }

    double DisplayTextDisplayEntity::GetWidth() const
    {
        return 0.0;
    }

    double DisplayTextDisplayEntity::GetHeight() const
    {
        return 0.0;
    }


    std::string DisplayTextDisplayEntity::GetClassName()
    {
        return "text_display";
    }

    EntityType DisplayTextDisplayEntity::GetClassType()
    {
        return EntityType::DisplayTextDisplay;
    }
    


    ProtocolCraft::Json::Value DisplayTextDisplayEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = DisplayEntity::Serialize();
        
        output["metadata"]["data_text_id"] = GetDataTextId().Serialize();
        output["metadata"]["data_line_width_id"] = GetDataLineWidthId();
        output["metadata"]["data_background_color_id"] = GetDataBackgroundColorId();
        output["metadata"]["data_text_opacity_id"] = GetDataTextOpacityId();
        output["metadata"]["data_style_flags_id"] = GetDataStyleFlagsId();

        return output;
    }


    void DisplayTextDisplayEntity::SetMetadataValue(const int index, const std::any& value)
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

    
    const ProtocolCraft::Chat& DisplayTextDisplayEntity::GetDataTextId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const ProtocolCraft::Chat&>(metadata.at("data_text_id"));
    }
    
    int DisplayTextDisplayEntity::GetDataLineWidthId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_line_width_id"));
    }
    
    int DisplayTextDisplayEntity::GetDataBackgroundColorId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_background_color_id"));
    }
    
    char DisplayTextDisplayEntity::GetDataTextOpacityId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_text_opacity_id"));
    }
    
    char DisplayTextDisplayEntity::GetDataStyleFlagsId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_style_flags_id"));
    }
    
    
    void DisplayTextDisplayEntity::SetDataTextId(const ProtocolCraft::Chat& data_text_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_text_id"] = data_text_id;
    }
    
    void DisplayTextDisplayEntity::SetDataLineWidthId(const int data_line_width_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_line_width_id"] = data_line_width_id;
    }
    
    void DisplayTextDisplayEntity::SetDataBackgroundColorId(const int data_background_color_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_background_color_id"] = data_background_color_id;
    }
    
    void DisplayTextDisplayEntity::SetDataTextOpacityId(const char data_text_opacity_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_text_opacity_id"] = data_text_opacity_id;
    }
    
    void DisplayTextDisplayEntity::SetDataStyleFlagsId(const char data_style_flags_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_style_flags_id"] = data_style_flags_id;
    }
    

}
#endif
