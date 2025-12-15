#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "botcraft/Game/Entities/entities/vehicle/boat/AbstractBoatEntity.hpp"

namespace Botcraft
{
    class AbstractChestBoatEntity : public AbstractBoatEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractBoatEntity::metadata_count + AbstractBoatEntity::hierarchy_metadata_count;

    public:
        AbstractChestBoatEntity();
        virtual ~AbstractChestBoatEntity();

        virtual bool IsAbstractChestBoat() const override;

    };
}
#endif
