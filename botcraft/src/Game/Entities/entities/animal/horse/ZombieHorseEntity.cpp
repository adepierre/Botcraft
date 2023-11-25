#include "botcraft/Game/Entities/entities/animal/horse/ZombieHorseEntity.hpp"

namespace Botcraft
{
    ZombieHorseEntity::ZombieHorseEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 15.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
    }

    ZombieHorseEntity::~ZombieHorseEntity()
    {

    }


    std::string ZombieHorseEntity::GetName() const
    {
        return "zombie_horse";
    }

    EntityType ZombieHorseEntity::GetType() const
    {
        return EntityType::ZombieHorse;
    }


    std::string ZombieHorseEntity::GetClassName()
    {
        return "zombie_horse";
    }

    EntityType ZombieHorseEntity::GetClassType()
    {
        return EntityType::ZombieHorse;
    }


    double ZombieHorseEntity::GetWidthImpl() const
    {
        return 1.3964844;
    }

    double ZombieHorseEntity::GetHeightImpl() const
    {
        return 1.6;
    }

}
