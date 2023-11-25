#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
#include "botcraft/Game/Entities/entities/monster/piglin/PiglinBruteEntity.hpp"

namespace Botcraft
{
    PiglinBruteEntity::PiglinBruteEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 50.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.35) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 7.0) });
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
