#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/animal/SalmonEntity.hpp"

namespace Botcraft
{
    SalmonEntity::SalmonEntity()
    {

    }

    SalmonEntity::~SalmonEntity()
    {

    }


    std::string SalmonEntity::GetName() const
    {
        return "salmon";
    }

    EntityType SalmonEntity::GetType() const
    {
        return EntityType::Salmon;
    }


    std::string SalmonEntity::GetClassName()
    {
        return "salmon";
    }

    EntityType SalmonEntity::GetClassType()
    {
        return EntityType::Salmon;
    }


    double SalmonEntity::GetWidthImpl() const
    {
        return 0.7;
    }

    double SalmonEntity::GetHeightImpl() const
    {
        return 0.4;
    }

}
#endif
