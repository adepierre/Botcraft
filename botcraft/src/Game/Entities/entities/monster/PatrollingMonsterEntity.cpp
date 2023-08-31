#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/monster/PatrollingMonsterEntity.hpp"

namespace Botcraft
{
    PatrollingMonsterEntity::PatrollingMonsterEntity()
    {

    }

    PatrollingMonsterEntity::~PatrollingMonsterEntity()
    {

    }

    bool PatrollingMonsterEntity::IsPatrollingMonster() const
    {
        return true;
    }

}
#endif
