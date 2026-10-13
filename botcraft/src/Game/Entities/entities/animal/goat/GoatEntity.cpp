#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "botcraft/Game/Entities/entities/animal/goat/GoatEntity.hpp"

namespace Botcraft
{
    GoatEntity::GoatEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataIsScreamingGoat(false);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SetDataHasLeftHorn(true);
        SetDataHasRightHorn(true);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 2.0) });
    }

    GoatEntity::~GoatEntity()
    {

    }


    std::string GoatEntity::GetName() const
    {
        return "goat";
    }

    EntityType GoatEntity::GetType() const
    {
        return EntityType::Goat;
    }


    std::string GoatEntity::GetClassName()
    {
        return "goat";
    }

    EntityType GoatEntity::GetClassType()
    {
        return EntityType::Goat;
    }


    ProtocolCraft::Json::Value GoatEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_is_screaming_goat"] = GetDataIsScreamingGoat();
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        output["metadata"]["data_has_left_horn"] = GetDataHasLeftHorn();
        output["metadata"]["data_has_right_horn"] = GetDataHasRightHorn();
#endif

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


    bool GoatEntity::GetDataIsScreamingGoat() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_screaming_goat"));
    }

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    bool GoatEntity::GetDataHasLeftHorn() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_has_left_horn"));
    }

    bool GoatEntity::GetDataHasRightHorn() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_has_right_horn"));
    }
#endif


    void GoatEntity::SetDataIsScreamingGoat(const bool data_is_screaming_goat)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_screaming_goat"), data_is_screaming_goat);
    }

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    void GoatEntity::SetDataHasLeftHorn(const bool data_has_left_horn)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_has_left_horn"), data_has_left_horn);
    }

    void GoatEntity::SetDataHasRightHorn(const bool data_has_right_horn)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_has_right_horn"), data_has_right_horn);
    }
#endif


    double GoatEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }


    double GoatEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double GoatEntity::GetHeightImpl() const
    {
        return 1.3;
    }

}
#endif
