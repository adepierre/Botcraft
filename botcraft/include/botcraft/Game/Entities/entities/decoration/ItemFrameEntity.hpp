#pragma once

#include "botcraft/Game/Entities/entities/decoration/HangingEntity.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace Botcraft
{
    class ItemFrameEntity : public HangingEntity
    {
    protected:
        static constexpr int metadata_count = 2;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = HangingEntity::metadata_count + HangingEntity::hierarchy_metadata_count;

    public:
        ItemFrameEntity();
        virtual ~ItemFrameEntity();

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

        ProtocolCraft::Slot GetDataItem() const;
        int GetDataRotation() const;

        void SetDataItem(const ProtocolCraft::Slot& data_item);
        void SetDataRotation(const int data_rotation);

    };
}
