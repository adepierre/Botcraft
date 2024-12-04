#if PROTOCOL_VERSION > 767 /* > 1.21.1 */ && PROTOCOL_VERSION < 769 /* < 1.21.4 */
#include "botcraft/Game/Entities/entities/monster/creaking/CreakingTransientEntity.hpp"

namespace Botcraft
{
    CreakingTransientEntity::CreakingTransientEntity()
    {

    }

    CreakingTransientEntity::~CreakingTransientEntity()
    {

    }


    std::string CreakingTransientEntity::GetName() const
    {
        return "creaking_transient";
    }

    EntityType CreakingTransientEntity::GetType() const
    {
        return EntityType::CreakingTransient;
    }


    std::string CreakingTransientEntity::GetClassName()
    {
        return "creaking_transient";
    }

    EntityType CreakingTransientEntity::GetClassType()
    {
        return EntityType::CreakingTransient;
    }
}
#endif
