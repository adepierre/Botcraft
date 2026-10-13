#pragma once

#include "botcraft/Game/Entities/entities/decoration/HangingEntity.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace Botcraft
{
    class ItemFrameEntity : public HangingEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_item"),
            std::string_view("data_rotation"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = HangingEntity::metadata_count + HangingEntity::hierarchy_metadata_count;

    public:
        ItemFrameEntity();
        virtual ~ItemFrameEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        ProtocolCraft::Slot GetDataItem() const;
        int GetDataRotation() const;

        void SetDataItem(const ProtocolCraft::Slot& data_item);
        void SetDataRotation(const int data_rotation);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
