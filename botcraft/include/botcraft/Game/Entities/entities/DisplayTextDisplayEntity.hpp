#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "botcraft/Game/Entities/entities/DisplayEntity.hpp"

namespace Botcraft
{
    class DisplayTextDisplayEntity : public DisplayEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_text_id"),
            std::string_view("data_line_width_id"),
            std::string_view("data_background_color_id"),
            std::string_view("data_text_opacity_id"),
            std::string_view("data_style_flags_id"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = DisplayEntity::metadata_count + DisplayEntity::hierarchy_metadata_count;

    public:
        DisplayTextDisplayEntity();
        virtual ~DisplayTextDisplayEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
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

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
