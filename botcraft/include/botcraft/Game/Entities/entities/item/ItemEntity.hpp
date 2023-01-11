#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace Botcraft
{
    class ItemEntity : public Entity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        ItemEntity();
        virtual ~ItemEntity();

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

        const ProtocolCraft::Slot& GetDataItem() const;

        void SetDataItem(const ProtocolCraft::Slot& data_item);

    };
}
