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

    double SalmonEntity::GetWidth() const
    {
        return 0.7;
    }

    double SalmonEntity::GetHeight() const
    {
        return 0.4;
    }


    std::string SalmonEntity::GetClassName()
    {
        return "salmon";
    }

    EntityType SalmonEntity::GetClassType()
    {
        return EntityType::Salmon;
    }

}
#endif
