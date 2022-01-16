#if PROTOCOL_VERSION > 736
#include "botcraft/Game/Entities/entities/monster/piglin/PiglinBruteEntity.hpp"

namespace Botcraft
{
    PiglinBruteEntity::PiglinBruteEntity()
    {

    }

    PiglinBruteEntity::~PiglinBruteEntity()
    {

    }


    std::string PiglinBruteEntity::GetName() const
    {
        return "PiglinBrute";
    }

    EntityType PiglinBruteEntity::GetType() const
    {
        return EntityType::PiglinBrute;
    }

    double PiglinBruteEntity::GetWidth() const
    {
        return 0.6;
    }

    double PiglinBruteEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string PiglinBruteEntity::GetClassName()
    {
        return "PiglinBrute";
    }

    EntityType PiglinBruteEntity::GetClassType()
    {
        return EntityType::PiglinBrute;
    }

}
#endif
