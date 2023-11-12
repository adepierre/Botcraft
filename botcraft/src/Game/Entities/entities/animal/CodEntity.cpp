#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
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


    std::string CodEntity::GetClassName()
    {
        return "cod";
    }

    EntityType CodEntity::GetClassType()
    {
        return EntityType::Cod;
    }


    double CodEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double CodEntity::GetHeightImpl() const
    {
        return 0.3;
    }

}
#endif
