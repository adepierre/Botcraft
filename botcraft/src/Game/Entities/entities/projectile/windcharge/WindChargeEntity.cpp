#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/Entities/entities/projectile/windcharge/WindChargeEntity.hpp"

#include <mutex>

namespace Botcraft
{
    WindChargeEntity::WindChargeEntity()
    {

    }

    WindChargeEntity::~WindChargeEntity()
    {

    }


    std::string WindChargeEntity::GetName() const
    {
        return "wind_charge";
    }

    EntityType WindChargeEntity::GetType() const
    {
        return EntityType::WindCharge;
    }


    std::string WindChargeEntity::GetClassName()
    {
        return "wind_charge";
    }

    EntityType WindChargeEntity::GetClassType()
    {
        return EntityType::WindCharge;
    }


    double WindChargeEntity::GetWidthImpl() const
    {
        return 0.3125;
    }

    double WindChargeEntity::GetHeightImpl() const
    {
        return 0.3125;
    }

}
#endif
