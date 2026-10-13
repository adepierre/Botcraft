#include "botcraft/Game/Entities/entities/monster/EnderManEntity.hpp"

namespace Botcraft
{
    EnderManEntity::EnderManEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataCarryState(0);
        SetDataCreepy(false);
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        SetDataStaredAt(false);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 40.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 7.0) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 64.0) });
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 1.0) });
#endif
    }

    EnderManEntity::~EnderManEntity()
    {

    }


    std::string EnderManEntity::GetName() const
    {
        return "enderman";
    }

    EntityType EnderManEntity::GetType() const
    {
        return EntityType::EnderMan;
    }


    std::string EnderManEntity::GetClassName()
    {
        return "enderman";
    }

    EntityType EnderManEntity::GetClassType()
    {
        return EntityType::EnderMan;
    }


    ProtocolCraft::Json::Value EnderManEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_carry_state"] = GetDataCarryState();
        output["metadata"]["data_creepy"] = GetDataCreepy();
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        output["metadata"]["data_stared_at"] = GetDataStaredAt();
#endif

        return output;
    }


    int EnderManEntity::GetDataCarryState() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_carry_state"));
    }

    bool EnderManEntity::GetDataCreepy() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_creepy"));
    }

#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
    bool EnderManEntity::GetDataStaredAt() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_stared_at"));
    }
#endif


    void EnderManEntity::SetDataCarryState(const int data_carry_state)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_carry_state"), data_carry_state);
    }

    void EnderManEntity::SetDataCreepy(const bool data_creepy)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_creepy"), data_creepy);
    }

#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
    void EnderManEntity::SetDataStaredAt(const bool data_stared_at)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_stared_at"), data_stared_at);
    }
#endif


    double EnderManEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double EnderManEntity::GetHeightImpl() const
    {
        return 2.9;
    }

}
