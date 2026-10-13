#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "botcraft/Game/Entities/entities/DisplayEntity.hpp"

namespace Botcraft
{
    class DisplayItemDisplayEntity : public DisplayEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_item_stack_id"),
            std::string_view("data_item_display_id"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = DisplayEntity::metadata_count + DisplayEntity::hierarchy_metadata_count;

    public:
        DisplayItemDisplayEntity();
        virtual ~DisplayItemDisplayEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        ProtocolCraft::Slot GetDataItemStackId() const;
        char GetDataItemDisplayId() const;

        void SetDataItemStackId(const ProtocolCraft::Slot& data_item_stack_id);
        void SetDataItemDisplayId(const char data_item_display_id);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
