#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/monster/ZombifiedPiglinEntity.hpp"

namespace Botcraft
{
    ZombifiedPiglinEntity::ZombifiedPiglinEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::ZombieSpawnReinforcementsChance, EntityAttribute(EntityAttribute::Type::ZombieSpawnReinforcementsChance, 0.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.23) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 5.0) });
    }

    ZombifiedPiglinEntity::~ZombifiedPiglinEntity()
    {

    }


    std::string ZombifiedPiglinEntity::GetName() const
    {
        return "zombified_piglin";
    }

    EntityType ZombifiedPiglinEntity::GetType() const
    {
        return EntityType::ZombifiedPiglin;
    }


    std::string ZombifiedPiglinEntity::GetClassName()
    {
        return "zombified_piglin";
    }

    EntityType ZombifiedPiglinEntity::GetClassType()
    {
        return EntityType::ZombifiedPiglin;
    }


    double ZombifiedPiglinEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double ZombifiedPiglinEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
#endif
