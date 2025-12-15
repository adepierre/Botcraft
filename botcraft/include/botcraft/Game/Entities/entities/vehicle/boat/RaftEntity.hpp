#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "botcraft/Game/Entities/entities/vehicle/boat/AbstractBoatEntity.hpp"

namespace Botcraft
{
    class RaftEntity : public AbstractBoatEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractBoatEntity::metadata_count + AbstractBoatEntity::hierarchy_metadata_count;

    public:
        RaftEntity(const EntityType type);
        virtual ~RaftEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        virtual bool IsRaft() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

    protected:
        const EntityType type;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
