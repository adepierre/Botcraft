#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class BlockAttachedEntity : public Entity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        BlockAttachedEntity();
        virtual ~BlockAttachedEntity();

        virtual bool IsBlockAttachedEntity() const override;
    };
}
#endif
