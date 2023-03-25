#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/monster/ZombifiedPiglinEntity.hpp"

namespace Botcraft
{
    ZombifiedPiglinEntity::ZombifiedPiglinEntity()
    {

    }

    ZombifiedPiglinEntity::~ZombifiedPiglinEntity()
    {

    }


    std::string ZombifiedPiglinEntity::GetName() const
    {
        return "zombified_piglin";
    }

    EntityType ZombifiedPiglinEntity::GetType() const
    {
        return EntityType::ZombifiedPiglin;
    }

    double ZombifiedPiglinEntity::GetWidth() const
    {
        return 0.6;
    }

    double ZombifiedPiglinEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string ZombifiedPiglinEntity::GetClassName()
    {
        return "zombified_piglin";
    }

    EntityType ZombifiedPiglinEntity::GetClassType()
    {
        return EntityType::ZombifiedPiglin;
    }

}
#endif
