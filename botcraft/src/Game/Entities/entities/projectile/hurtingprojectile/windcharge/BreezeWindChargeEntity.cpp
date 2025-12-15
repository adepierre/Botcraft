#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/Entities/entities/projectile/hurtingprojectile/windcharge/BreezeWindChargeEntity.hpp"

namespace Botcraft
{
    BreezeWindChargeEntity::BreezeWindChargeEntity()
    {

    }

    BreezeWindChargeEntity::~BreezeWindChargeEntity()
    {

    }


    std::string BreezeWindChargeEntity::GetName() const
    {
        return "breeze_wind_charge";
    }

    EntityType BreezeWindChargeEntity::GetType() const
    {
        return EntityType::BreezeWindCharge;
    }


    std::string BreezeWindChargeEntity::GetClassName()
    {
        return "breeze_wind_charge";
    }

    EntityType BreezeWindChargeEntity::GetClassType()
    {
        return EntityType::BreezeWindCharge;
    }


    double BreezeWindChargeEntity::GetWidthImpl() const
    {
        return 0.3125;
    }

    double BreezeWindChargeEntity::GetHeightImpl() const
    {
        return 0.3125;
    }

}
#endif
