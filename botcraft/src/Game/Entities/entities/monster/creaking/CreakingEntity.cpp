#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "botcraft/Game/Entities/entities/monster/creaking/CreakingEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, CreakingEntity::metadata_count> CreakingEntity::metadata_names{ {
        "can_move",
        "is_active",
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        "is_tearing_down",
        "home_pose",
#endif
    } };

    CreakingEntity::CreakingEntity()
    {
        // Initialize all metadata with default values
        SetCanMove(true);
        SetIsActive(false);
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        SetIsTearingDown(false);
        SetHomePos(std::nullopt);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 1.0) });
#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 2.0) });
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 1.0) });
#else
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.4) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 3.0) });
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 1.0625) });
#endif
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 32.0) });
    }

    CreakingEntity::~CreakingEntity()
    {

    }


    std::string CreakingEntity::GetName() const
    {
        return "creaking";
    }

    EntityType CreakingEntity::GetType() const
    {
        return EntityType::Creaking;
    }


    std::string CreakingEntity::GetClassName()
    {
        return "creaking";
    }

    EntityType CreakingEntity::GetClassType()
    {
        return EntityType::Creaking;
    }


    ProtocolCraft::Json::Value CreakingEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["can_move"] = GetCanMove();
        output["metadata"]["is_active"] = GetIsActive();
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        output["metadata"]["is_tearing_down"] = GetIsTearingDown();
        output["metadata"]["is_tearing_down"] = GetHomePos() ? GetHomePos().value().Serialize() : ProtocolCraft::Json::Value(nullptr);
#endif


        return output;
    }


    void CreakingEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool CreakingEntity::GetCanMove() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("can_move"));
    }

    bool CreakingEntity::GetIsActive() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("is_active"));
    }

#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
    bool CreakingEntity::GetIsTearingDown() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("is_tearing_down"));
    }

    const std::optional<Position>& CreakingEntity::GetHomePos() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const std::optional<Position>&>(metadata.at("home_pos"));
    }
#endif


    void CreakingEntity::SetCanMove(const bool can_move)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["can_move"] = can_move;
    }

    void CreakingEntity::SetIsActive(const bool is_active)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["is_active"] = is_active;
    }

#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
    void CreakingEntity::SetIsTearingDown(const bool is_tearing_down)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["is_tearing_down"] = is_tearing_down;
    }

    void CreakingEntity::SetHomePos(const std::optional<Position>& home_pos)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["home_pos"] = home_pos;
    }
#endif


    double CreakingEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double CreakingEntity::GetHeightImpl() const
    {
        return 2.7;
    }

}
#endif
