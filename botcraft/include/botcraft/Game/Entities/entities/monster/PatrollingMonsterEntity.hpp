#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class PatrollingMonsterEntity : public MonsterEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        PatrollingMonsterEntity();
        virtual ~PatrollingMonsterEntity();

        virtual bool IsPatrollingMonster() const override;
    };
}
#endif
