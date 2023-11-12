#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
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
        return "piglin_brute";
    }

    EntityType PiglinBruteEntity::GetType() const
    {
        return EntityType::PiglinBrute;
    }


    std::string PiglinBruteEntity::GetClassName()
    {
        return "piglin_brute";
    }

    EntityType PiglinBruteEntity::GetClassType()
    {
        return EntityType::PiglinBrute;
    }


    double PiglinBruteEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double PiglinBruteEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
#endif
