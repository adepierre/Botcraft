#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "botcraft/Game/Entities/entities/DisplayEntity.hpp"

namespace Botcraft
{
    class DisplayTextDisplayEntity : public DisplayEntity
    {
    protected:
        static constexpr int metadata_count = 5;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = DisplayEntity::metadata_count + DisplayEntity::hierarchy_metadata_count;

    public:
        DisplayTextDisplayEntity();
        virtual ~DisplayTextDisplayEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();
        

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        ProtocolCraft::Chat GetDataTextId() const;
        int GetDataLineWidthId() const;
        int GetDataBackgroundColorId() const;
        char GetDataTextOpacityId() const;
        char GetDataStyleFlagsId() const;
        
        void SetDataTextId(const ProtocolCraft::Chat& data_text_id);
        void SetDataLineWidthId(const int data_line_width_id);
        void SetDataBackgroundColorId(const int data_background_color_id);
        void SetDataTextOpacityId(const char data_text_opacity_id);
        void SetDataStyleFlagsId(const char data_style_flags_id);
        
    };
}
#endif
