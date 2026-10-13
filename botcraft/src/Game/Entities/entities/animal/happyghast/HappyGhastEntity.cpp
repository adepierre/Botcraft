#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "botcraft/Game/Entities/entities/animal/happyghast/HappyGhastEntity.hpp"

namespace Botcraft
{
    HappyGhastEntity::HappyGhastEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetIsLeashHolder(false);
        SetStaysStill(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 20.0) });
        attributes.insert({ EntityAttribute::Type::TemptRange, EntityAttribute(EntityAttribute::Type::TemptRange, 16.0) });
        attributes.insert({ EntityAttribute::Type::FlyingSpeed, EntityAttribute(EntityAttribute::Type::FlyingSpeed, 0.05) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.05) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 16.0) });
        attributes.insert({ EntityAttribute::Type::CameraDistance, EntityAttribute(EntityAttribute::Type::CameraDistance, 8.0) });
    }

    HappyGhastEntity::~HappyGhastEntity()
    {

    }


    std::string HappyGhastEntity::GetName() const
    {
        return "happy_ghast";
    }

    EntityType HappyGhastEntity::GetType() const
    {
        return EntityType::HappyGhast;
    }


    std::string HappyGhastEntity::GetClassName()
    {
        return "happy_ghast";
    }

    EntityType HappyGhastEntity::GetClassType()
    {
        return EntityType::HappyGhast;
    }


    ProtocolCraft::Json::Value HappyGhastEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["is_leash_holder"] = GetIsLeashHolder();
        output["metadata"]["stays_still"] = GetStaysStill();

        output["attributes"]["flying_speed"] = GetAttributeFlyingSpeedValue();

        return output;
    }


    bool HappyGhastEntity::GetIsLeashHolder() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("is_leash_holder"));
    }

    bool HappyGhastEntity::GetStaysStill() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("stays_still"));
    }


    void HappyGhastEntity::SetIsLeashHolder(const int is_leash_holder)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("is_leash_holder"), is_leash_holder);
    }

    void HappyGhastEntity::SetStaysStill(const int stays_still)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("stays_still"), stays_still);
    }


    double HappyGhastEntity::GetAttributeFlyingSpeedValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::FlyingSpeed).GetValue();
    }


    double HappyGhastEntity::GetWidthImpl() const
    {
        return 4.0;
    }

    double HappyGhastEntity::GetHeightImpl() const
    {
        return 4.0;
    }

}
#endif
