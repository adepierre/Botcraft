#include "botcraft/Game/Entities/entities/monster/GhastEntity.hpp"

namespace Botcraft
{
    GhastEntity::GhastEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataIsCharging(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 100.0) });
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        attributes.insert({ EntityAttribute::Type::CameraDistance, EntityAttribute(EntityAttribute::Type::CameraDistance, 8.0) });
        attributes.insert({ EntityAttribute::Type::FlyingSpeed, EntityAttribute(EntityAttribute::Type::FlyingSpeed, 0.06) });
#endif
    }

    GhastEntity::~GhastEntity()
    {

    }


    std::string GhastEntity::GetName() const
    {
        return "ghast";
    }

    EntityType GhastEntity::GetType() const
    {
        return EntityType::Ghast;
    }


    std::string GhastEntity::GetClassName()
    {
        return "ghast";
    }

    EntityType GhastEntity::GetClassType()
    {
        return EntityType::Ghast;
    }


    ProtocolCraft::Json::Value GhastEntity::Serialize() const
    {
#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
        ProtocolCraft::Json::Value output = FlyingMobEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = MobEntity::Serialize();
#endif

        output["metadata"]["data_is_charging"] = GetDataIsCharging();

#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        output["attributes"]["flying_speed"] = GetAttributeFlyingSpeedValue();
#endif

        return output;
    }


    bool GhastEntity::GetDataIsCharging() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_charging"));
    }


    void GhastEntity::SetDataIsCharging(const bool data_is_charging)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_charging"), data_is_charging);
    }


#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
    double GhastEntity::GetAttributeFlyingSpeedValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::FlyingSpeed).GetValue();
    }
#endif


    double GhastEntity::GetWidthImpl() const
    {
        return 4.0;
    }

    double GhastEntity::GetHeightImpl() const
    {
        return 4.0;
    }

}
