#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace Botcraft
{
    class ItemEntity : public Entity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_item"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        ItemEntity();
        virtual ~ItemEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        ProtocolCraft::Slot GetDataItem() const;

        void SetDataItem(const ProtocolCraft::Slot& data_item);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
