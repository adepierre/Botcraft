#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "botcraft/Game/Entities/entities/vehicle/boat/AbstractChestBoatEntity.hpp"

namespace Botcraft
{
    class ChestRaftEntity : public AbstractChestBoatEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractChestBoatEntity::metadata_count + AbstractChestBoatEntity::hierarchy_metadata_count;

    public:
        ChestRaftEntity(const EntityType type);
        virtual ~ChestRaftEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        virtual bool IsChestRaft() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

    protected:
        const EntityType type;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
