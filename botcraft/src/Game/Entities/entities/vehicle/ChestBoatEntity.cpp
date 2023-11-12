#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "botcraft/Game/Entities/entities/vehicle/ChestBoatEntity.hpp"

namespace Botcraft
{
    ChestBoatEntity::ChestBoatEntity()
    {

    }

    ChestBoatEntity::~ChestBoatEntity()
    {

    }


    std::string ChestBoatEntity::GetName() const
    {
        return "chest_boat";
    }

    EntityType ChestBoatEntity::GetType() const
    {
        return EntityType::ChestBoat;
    }


    std::string ChestBoatEntity::GetClassName()
    {
        return "chest_boat";
    }

    EntityType ChestBoatEntity::GetClassType()
    {
        return EntityType::ChestBoat;
    }


    double ChestBoatEntity::GetWidthImpl() const
    {
        return 1.375;
    }

    double ChestBoatEntity::GetHeightImpl() const
    {
        return 0.5625;
    }

}
#endif
