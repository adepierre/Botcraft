#include "botcraft/Game/Entities/entities/MobEntity.hpp"

namespace Botcraft
{
    MobEntity::MobEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataMobFlagsId(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 16.0) });
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 767 /* < 1.21 */
        attributes.insert({ EntityAttribute::Type::AttackKnockback, EntityAttribute(EntityAttribute::Type::AttackKnockback, 0.0) });
#endif
    }

    MobEntity::~MobEntity()
    {

    }

    bool MobEntity::IsMob() const
    {
        return true;
    }


    ProtocolCraft::Json::Value MobEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = LivingEntity::Serialize();

        output["metadata"]["data_mob_flags_id"] = GetDataMobFlagsId();

        output["attributes"]["follow_range"] = GetAttributeFollowRangeValue();
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 767 /* < 1.21 */
        output["attributes"]["attack_knockback"] = GetAttributeAttackKnockbackValue();
#endif

        return output;
    }


    char MobEntity::GetDataMobFlagsId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_mob_flags_id"));
    }


    void MobEntity::SetDataMobFlagsId(const char data_mob_flags_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_mob_flags_id"), data_mob_flags_id);
    }


    double MobEntity::GetAttributeFollowRangeValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::FollowRange).GetValue();
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 767 /* < 1.21 */
    double MobEntity::GetAttributeAttackKnockbackValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackKnockback).GetValue();
    }
#endif

}
