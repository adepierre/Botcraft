#if PROTOCOL_VERSION > 340
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
        return "Salmon";
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
        return "Salmon";
    }

    EntityType SalmonEntity::GetClassType()
    {
        return EntityType::Salmon;
    }

}
#endif
