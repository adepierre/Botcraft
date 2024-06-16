#pragma once

#if PROTOCOL_VERSION < 767 /* < 1.21 */
#include "botcraft/Game/Entities/entities/Entity.hpp"
#else
#include "botcraft/Game/Entities/entities/decoration/BlockAttachedEntity.hpp"
#endif

namespace Botcraft
{
    class HangingEntity :
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        public Entity
#else
        public BlockAttachedEntity
#endif
    {
    protected:
        static constexpr int metadata_count = 0;
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = BlockAttachedEntity::metadata_count + BlockAttachedEntity::hierarchy_metadata_count;
#endif

    public:
        HangingEntity();
        virtual ~HangingEntity();

        virtual bool IsHangingEntity() const override;
    };
}
