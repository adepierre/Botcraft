#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "botcraft/Game/Entities/entities/DisplayTextDisplayEntity.hpp"

namespace Botcraft
{
    DisplayTextDisplayEntity::DisplayTextDisplayEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    ProtocolCraft::Chat DisplayTextDisplayEntity::GetDataTextId() const
    {
        return GetMetadata<ProtocolCraft::Chat>(BOTCRAFT_ENTITY_METADATA_INDEX("data_text_id"));
    }

    int DisplayTextDisplayEntity::GetDataLineWidthId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_line_width_id"));
    }

    int DisplayTextDisplayEntity::GetDataBackgroundColorId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_background_color_id"));
    }

    char DisplayTextDisplayEntity::GetDataTextOpacityId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_text_opacity_id"));
    }

    char DisplayTextDisplayEntity::GetDataStyleFlagsId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_style_flags_id"));
    }


    void DisplayTextDisplayEntity::SetDataTextId(const ProtocolCraft::Chat& data_text_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_text_id"), data_text_id);
    }

    void DisplayTextDisplayEntity::SetDataLineWidthId(const int data_line_width_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_line_width_id"), data_line_width_id);
    }

    void DisplayTextDisplayEntity::SetDataBackgroundColorId(const int data_background_color_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_background_color_id"), data_background_color_id);
    }

    void DisplayTextDisplayEntity::SetDataTextOpacityId(const char data_text_opacity_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_text_opacity_id"), data_text_opacity_id);
    }

    void DisplayTextDisplayEntity::SetDataStyleFlagsId(const char data_style_flags_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_style_flags_id"), data_style_flags_id);
    }


    double DisplayTextDisplayEntity::GetWidthImpl() const
    {
        return 0.0;
    }

    double DisplayTextDisplayEntity::GetHeightImpl() const
    {
        return 0.0;
    }

}
#endif
