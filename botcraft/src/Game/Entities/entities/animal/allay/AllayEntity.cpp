#if PROTOCOL_VERSION > 758
#include "botcraft/Game/Entities/entities/animal/allay/AllayEntity.hpp"

namespace Botcraft
{
    AllayEntity::AllayEntity()
    {

    }

    AllayEntity::~AllayEntity()
    {

    }


    std::string AllayEntity::GetName() const
    {
        return "Allay";
    }

    EntityType AllayEntity::GetType() const
    {
        return EntityType::Allay;
    }

    double AllayEntity::GetWidth() const
    {
        return 0.35;
    }

    double AllayEntity::GetHeight() const
    {
        return 0.6;
    }


    std::string AllayEntity::GetClassName()
    {
        return "Allay";
    }

    EntityType AllayEntity::GetClassType()
    {
        return EntityType::Allay;
    }

}
#endif
