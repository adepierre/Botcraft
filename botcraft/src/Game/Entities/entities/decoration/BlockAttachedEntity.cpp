#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#include "botcraft/Game/Entities/entities/decoration/BlockAttachedEntity.hpp"

#include <mutex>

namespace Botcraft
{
    BlockAttachedEntity::BlockAttachedEntity()
    {

    }

    BlockAttachedEntity::~BlockAttachedEntity()
    {

    }


    bool BlockAttachedEntity::IsBlockAttachedEntity() const
    {
        return true;
    }

}
#endif
