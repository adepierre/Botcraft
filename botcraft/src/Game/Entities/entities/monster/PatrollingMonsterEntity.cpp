#if PROTOCOL_VERSION > 404
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
