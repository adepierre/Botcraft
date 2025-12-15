#if PROTOCOL_VERSION < 579 /* < 1.16 */
#include "botcraft/Game/Entities/entities/monster/zombie/PigZombieEntity.hpp"

namespace Botcraft
{
    PigZombieEntity::PigZombieEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::ZombieSpawnReinforcementsChance, EntityAttribute(EntityAttribute::Type::ZombieSpawnReinforcementsChance, 0.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.23) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 5.0) });
    }

    PigZombieEntity::~PigZombieEntity()
    {

    }


    std::string PigZombieEntity::GetName() const
    {
        return "zombie_pigman";
    }

    EntityType PigZombieEntity::GetType() const
    {
        return EntityType::PigZombie;
    }


    std::string PigZombieEntity::GetClassName()
    {
        return "zombie_pigman";
    }

    EntityType PigZombieEntity::GetClassType()
    {
        return EntityType::PigZombie;
    }


    double PigZombieEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double PigZombieEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
#endif
