#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "botcraft/Game/Entities/entities/vehicle/boat/AbstractChestBoatEntity.hpp"


namespace Botcraft
{
    AbstractChestBoatEntity::AbstractChestBoatEntity()
    {

    }

    AbstractChestBoatEntity::~AbstractChestBoatEntity()
    {

    }


    bool AbstractChestBoatEntity::IsAbstractChestBoat() const
    {
        return true;
    }
}
#endif
