#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/monster/RavagerEntity.hpp"

namespace Botcraft
{
    RavagerEntity::RavagerEntity()
    {

    }

    RavagerEntity::~RavagerEntity()
    {

    }


    std::string RavagerEntity::GetName() const
    {
        return "ravager";
    }

    EntityType RavagerEntity::GetType() const
    {
        return EntityType::Ravager;
    }

    double RavagerEntity::GetWidth() const
    {
        return 1.95;
    }

    double RavagerEntity::GetHeight() const
    {
        return 2.2;
    }


    std::string RavagerEntity::GetClassName()
    {
        return "ravager";
    }

    EntityType RavagerEntity::GetClassType()
    {
        return EntityType::Ravager;
    }

}
#endif
