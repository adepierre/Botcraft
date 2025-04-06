#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include "botcraft/Game/Entities/entities/animal/AbstractCowEntity.hpp"

namespace Botcraft
{
    AbstractCowEntity::AbstractCowEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
    }

    AbstractCowEntity::~AbstractCowEntity()
    {

    }

    bool AbstractCowEntity::IsAbstractCow() const
    {
        return true;
    }

}
#endif
