#include "botcraft/Game/Entities/entities/MobEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, MobEntity::metadata_count> MobEntity::metadata_names{ {
        "data_mob_flags_id",
    } };

    MobEntity::MobEntity()
    {
        // Initialize all metadata with default values
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


    void MobEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            LivingEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char MobEntity::GetDataMobFlagsId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_mob_flags_id"));
    }


    void MobEntity::SetDataMobFlagsId(const char data_mob_flags_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_mob_flags_id"] = data_mob_flags_id;
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
