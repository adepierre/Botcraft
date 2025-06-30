#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "botcraft/Game/Entities/entities/animal/HappyGhastEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, HappyGhastEntity::metadata_count> HappyGhastEntity::metadata_names{ {
        "is_leash_holder",
        "stays_still",
    } };

    HappyGhastEntity::HappyGhastEntity()
    {
        // Initialize all metadata with default values
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


    void HappyGhastEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool HappyGhastEntity::GetIsLeashHolder() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("is_leash_holder"));
    }

    bool HappyGhastEntity::GetStaysStill() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("stays_still"));
    }


    void HappyGhastEntity::SetIsLeashHolder(const int is_leash_holder)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["is_leash_holder"] = is_leash_holder;
    }

    void HappyGhastEntity::SetStaysStill(const int stays_still)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["stays_still"] = stays_still;
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
