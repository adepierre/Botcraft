#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/monster/DrownedEntity.hpp"

namespace Botcraft
{
    DrownedEntity::DrownedEntity()
    {
        // Initialize all attributes with default values
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 1.0) });
#endif
    }

    DrownedEntity::~DrownedEntity()
    {

    }


    std::string DrownedEntity::GetName() const
    {
        return "drowned";
    }

    EntityType DrownedEntity::GetType() const
    {
        return EntityType::Drowned;
    }


    std::string DrownedEntity::GetClassName()
    {
        return "drowned";
    }

    EntityType DrownedEntity::GetClassType()
    {
        return EntityType::Drowned;
    }


    double DrownedEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double DrownedEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
#endif
