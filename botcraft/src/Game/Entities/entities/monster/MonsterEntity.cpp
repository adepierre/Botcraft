#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    MonsterEntity::MonsterEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 2.0) });
    }

    MonsterEntity::~MonsterEntity()
    {

    }

    ProtocolCraft::Json::Value MonsterEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = PathfinderMobEntity::Serialize();

        output["attributes"]["generic.attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }

    bool MonsterEntity::IsMonster() const
    {
        return true;
    }


    double MonsterEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }

}
