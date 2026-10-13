#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
#include "botcraft/Game/Entities/entities/animal/bee/BeeEntity.hpp"

namespace Botcraft
{
    BeeEntity::BeeEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataFlagsId(0);
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
        SetDataRemainingAngerTime(0);
#else
        SetDataAngerEndTime(0);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
        attributes.insert({ EntityAttribute::Type::FlyingSpeed, EntityAttribute(EntityAttribute::Type::FlyingSpeed, 0.6) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 2.0) });
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 48.0) });
#endif
    }

    BeeEntity::~BeeEntity()
    {

    }


    std::string BeeEntity::GetName() const
    {
        return "bee";
    }

    EntityType BeeEntity::GetType() const
    {
        return EntityType::Bee;
    }


    std::string BeeEntity::GetClassName()
    {
        return "bee";
    }

    EntityType BeeEntity::GetClassType()
    {
        return EntityType::Bee;
    }


    ProtocolCraft::Json::Value BeeEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_flags_id"] = GetDataFlagsId();
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
        output["metadata"]["data_remaining_anger_time"] = GetDataRemainingAngerTime();
#else
        output["metadata"]["data_anger_end_time"] = GetDataAngerEndTime();
#endif

        output["attributes"]["flying_speed"] = GetAttributeFlyingSpeedValue();
        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();


        return output;
    }


    char BeeEntity::GetDataFlagsId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_flags_id"));
    }

#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
    int BeeEntity::GetDataRemainingAngerTime() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_remaining_anger_time"));
    }
#else
    long long int BeeEntity::GetDataAngerEndTime() const
    {
        return GetMetadata<long long int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_anger_end_time"));
    }
#endif


    void BeeEntity::SetDataFlagsId(const char data_flags_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_flags_id"), data_flags_id);
    }

#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
    void BeeEntity::SetDataRemainingAngerTime(const int data_remaining_anger_time)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_remaining_anger_time"), data_remaining_anger_time);
    }
#else
    void BeeEntity::SetDataAngerEndTime(const long long int data_anger_end_time)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_anger_end_time"), data_anger_end_time);
    }
#endif


    double BeeEntity::GetAttributeFlyingSpeedValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::FlyingSpeed).GetValue();
    }

    double BeeEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }


    double BeeEntity::GetWidthImpl() const
    {
#if PROTOCOL_VERSION < 776 /* < 26.2 */
        return 0.7;
#else
        return 0.55;
#endif
    }

    double BeeEntity::GetHeightImpl() const
    {
#if PROTOCOL_VERSION < 776 /* < 26.2 */
        return 0.6;
#else
        return 0.5;
#endif
    }

}
#endif
