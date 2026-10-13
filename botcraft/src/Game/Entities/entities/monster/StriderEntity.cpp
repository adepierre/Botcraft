#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/monster/StriderEntity.hpp"

namespace Botcraft
{
    StriderEntity::StriderEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataBoostTime(0);
        SetDataSuffocating(false);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SetDataSaddleId(false);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.175) });
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 16.0) });
#endif
    }

    StriderEntity::~StriderEntity()
    {

    }


    std::string StriderEntity::GetName() const
    {
        return "strider";
    }

    EntityType StriderEntity::GetType() const
    {
        return EntityType::Strider;
    }


    std::string StriderEntity::GetClassName()
    {
        return "strider";
    }

    EntityType StriderEntity::GetClassType()
    {
        return EntityType::Strider;
    }


    ProtocolCraft::Json::Value StriderEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_boost_time"] = GetDataBoostTime();
        output["metadata"]["data_suffocating"] = GetDataSuffocating();
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        output["metadata"]["data_saddle_id"] = GetDataSaddleId();
#endif

        return output;
    }


    int StriderEntity::GetDataBoostTime() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_boost_time"));
    }

    bool StriderEntity::GetDataSuffocating() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_suffocating"));
    }

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    bool StriderEntity::GetDataSaddleId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_saddle_id"));
    }
#endif


    void StriderEntity::SetDataBoostTime(const int data_boost_time)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_boost_time"), data_boost_time);
    }

    void StriderEntity::SetDataSuffocating(const bool data_suffocating)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_suffocating"), data_suffocating);
    }

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    void StriderEntity::SetDataSaddleId(const bool data_saddle_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_saddle_id"), data_saddle_id);
    }
#endif


    double StriderEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double StriderEntity::GetHeightImpl() const
    {
        return 1.7;
    }

}
#endif
