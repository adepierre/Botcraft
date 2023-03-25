#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/animal/CodEntity.hpp"

namespace Botcraft
{
    CodEntity::CodEntity()
    {

    }

    CodEntity::~CodEntity()
    {

    }


    std::string CodEntity::GetName() const
    {
        return "cod";
    }

    EntityType CodEntity::GetType() const
    {
        return EntityType::Cod;
    }

    double CodEntity::GetWidth() const
    {
        return 0.5;
    }

    double CodEntity::GetHeight() const
    {
        return 0.3;
    }


    std::string CodEntity::GetClassName()
    {
        return "cod";
    }

    EntityType CodEntity::GetClassType()
    {
        return EntityType::Cod;
    }

}
#endif
