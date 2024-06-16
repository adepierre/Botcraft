#include "botcraft/Game/Entities/entities/player/PlayerEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, PlayerEntity::metadata_count> PlayerEntity::metadata_names{ {
        "data_player_absorption_id",
        "data_score_id",
        "data_player_mode_customisation",
        "data_player_main_hand",
        "data_shoulder_left",
        "data_shoulder_right",
    } };

    PlayerEntity::PlayerEntity()
    {
        // Initialize all metadata with default values
        SetDataPlayerAbsorptionId(0.0f);
        SetDataScoreId(0);
        SetDataPlayerModeCustomisation(0);
        SetDataPlayerMainHand(1);
        SetDataShoulderLeft(ProtocolCraft::NBT::Value());
        SetDataShoulderRight(ProtocolCraft::NBT::Value());

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 1.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.1) });
        attributes.insert({ EntityAttribute::Type::AttackSpeed, EntityAttribute(EntityAttribute::Type::AttackSpeed, 4.0) });
        attributes.insert({ EntityAttribute::Type::Luck, EntityAttribute(EntityAttribute::Type::Luck, 0.0) });
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        attributes.insert({ EntityAttribute::Type::PlayerBlockInteractionRange, EntityAttribute(EntityAttribute::Type::PlayerBlockInteractionRange, 4.5) });
        attributes.insert({ EntityAttribute::Type::PlayerEntityInteractionRange, EntityAttribute(EntityAttribute::Type::PlayerEntityInteractionRange, 3.0) });
        attributes.insert({ EntityAttribute::Type::PlayerBlockBreakSpeed, EntityAttribute(EntityAttribute::Type::PlayerBlockBreakSpeed, 1.0) });
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        attributes.insert({ EntityAttribute::Type::PlayerSubmergedMiningSpeed, EntityAttribute(EntityAttribute::Type::PlayerSubmergedMiningSpeed, 0.2) });
        attributes.insert({ EntityAttribute::Type::PlayerSneakingSpeed, EntityAttribute(EntityAttribute::Type::PlayerSneakingSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::PlayerMiningEfficiency, EntityAttribute(EntityAttribute::Type::PlayerMiningEfficiency, 0.0) });
        attributes.insert({ EntityAttribute::Type::PlayerSweepingDamageRatio, EntityAttribute(EntityAttribute::Type::PlayerSweepingDamageRatio, 0.0) });
#endif
    }

    PlayerEntity::~PlayerEntity()
    {

    }


    std::string PlayerEntity::GetName() const
    {
        return "player";
    }

    EntityType PlayerEntity::GetType() const
    {
        return EntityType::Player;
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    AABB PlayerEntity::GetCollider(const Pose pose) const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetColliderImpl(pose);
    }

    double PlayerEntity::GetHeight(const Pose pose) const
    {
        switch (pose)
        {
        case Pose::Crouching:
            return 1.5;
        case Pose::Sleeping:
        case Pose::Dying:
            return 0.2;
        case Pose::FallFlying:
        case Pose::Swimming:
        case Pose::SpinAttack:
            return 0.6;
        default:
            return 1.8;
        }
    }

    double PlayerEntity::GetWidth(const Pose pose) const
    {
        switch (pose)
        {
        case Pose::Sleeping:
        case Pose::Dying:
            return 0.2;
        default:
            return 0.6;
        }
    }
#endif

    double PlayerEntity::GetEyeHeight() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetEyeHeightImpl();
    }


    std::string PlayerEntity::GetClassName()
    {
        return "player";
    }

    EntityType PlayerEntity::GetClassType()
    {
        return EntityType::Player;
    }


    ProtocolCraft::Json::Value PlayerEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = LivingEntity::Serialize();

        output["metadata"]["data_player_absorption_id"] = GetDataPlayerAbsorptionId();
        output["metadata"]["data_score_id"] = GetDataScoreId();
        output["metadata"]["data_player_mode_customisation"] = GetDataPlayerModeCustomisation();
        output["metadata"]["data_player_main_hand"] = GetDataPlayerMainHand();
        output["metadata"]["data_shoulder_left"] = GetDataShoulderLeft().Serialize();
        output["metadata"]["data_shoulder_right"] = GetDataShoulderRight().Serialize();

        output["attributes"]["generic.attack_damage"] = GetAttributeAttackDamageValue();
        output["attributes"]["generic.attack_speed"] = GetAttributeAttackSpeedValue();
        output["attributes"]["generic.luck"] = GetAttributeLuckValue();
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        output["attributes"]["player.block_interaction_range"] = GetAttributePlayerBlockInteractionRangeValue();
        output["attributes"]["player.entity_interaction_range"] = GetAttributePlayerEntityInteractionRangeValue();
        output["attributes"]["player.block_break_speed"] = GetAttributePlayerBlockBreakSpeedValue();
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        output["attributes"]["player.submerged_mining_speed"] = GetAttributePlayerSubmergedMiningSpeedValue();
        output["attributes"]["player.sneaking_speed"] = GetAttributePlayerSneakingSpeedValue();
        output["attributes"]["player.mining_efficiency"] = GetAttributePlayerMiningEfficiencyValue();
        output["attributes"]["player.sweeping_damage_ratio"] = GetAttributePlayerSweepingDamageRatioValue();
#endif

        return output;
    }


    void PlayerEntity::SetMetadataValue(const int index, const std::any& value)
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

    float PlayerEntity::GetDataPlayerAbsorptionId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_player_absorption_id"));
    }

    int PlayerEntity::GetDataScoreId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_score_id"));
    }

    char PlayerEntity::GetDataPlayerModeCustomisation() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_player_mode_customisation"));
    }

    char PlayerEntity::GetDataPlayerMainHand() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_player_main_hand"));
    }

    ProtocolCraft::NBT::Value PlayerEntity::GetDataShoulderLeft() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<ProtocolCraft::NBT::Value>(metadata.at("data_shoulder_left"));
    }

    ProtocolCraft::NBT::Value PlayerEntity::GetDataShoulderRight() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<ProtocolCraft::NBT::Value>(metadata.at("data_shoulder_right"));
    }


    void PlayerEntity::SetDataPlayerAbsorptionId(const float data_player_absorption_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_player_absorption_id"] = data_player_absorption_id;
    }

    void PlayerEntity::SetDataScoreId(const int data_score_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_score_id"] = data_score_id;
    }

    void PlayerEntity::SetDataPlayerModeCustomisation(const char data_player_mode_customisation)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_player_mode_customisation"] = data_player_mode_customisation;
    }

    void PlayerEntity::SetDataPlayerMainHand(const char data_player_main_hand)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_player_main_hand"] = data_player_main_hand;
    }

    void PlayerEntity::SetDataShoulderLeft(const ProtocolCraft::NBT::Value& data_shoulder_left)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_shoulder_left"] = data_shoulder_left;
    }

    void PlayerEntity::SetDataShoulderRight(const ProtocolCraft::NBT::Value& data_shoulder_right)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_shoulder_right"] = data_shoulder_right;
    }

    bool PlayerEntity::IsRemotePlayer() const
    {
        return true;
    }


    double PlayerEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }

    double PlayerEntity::GetAttributeAttackSpeedValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackSpeed).GetValue();
    }

    double PlayerEntity::GetAttributeLuckValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::Luck).GetValue();
    }

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    double PlayerEntity::GetAttributePlayerBlockInteractionRangeValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::PlayerBlockInteractionRange).GetValue();
    }

    double PlayerEntity::GetAttributePlayerEntityInteractionRangeValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::PlayerEntityInteractionRange).GetValue();
    }

    double PlayerEntity::GetAttributePlayerBlockBreakSpeedValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::PlayerBlockBreakSpeed).GetValue();
    }
#endif

#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
    double PlayerEntity::GetAttributePlayerSubmergedMiningSpeedValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::PlayerSubmergedMiningSpeed).GetValue();
    }

    double PlayerEntity::GetAttributePlayerSneakingSpeedValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetAttributePlayerSneakingSpeedValueImpl();
    }

    double PlayerEntity::GetAttributePlayerSneakingSpeedValueImpl() const
    {
        return attributes.at(EntityAttribute::Type::PlayerSneakingSpeed).GetValue();
    }

    double PlayerEntity::GetAttributePlayerMiningEfficiencyValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::PlayerMiningEfficiency).GetValue();
    }

    double PlayerEntity::GetAttributePlayerSweepingDamageRatioValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::PlayerSweepingDamageRatio).GetValue();
    }
#endif


    double PlayerEntity::GetEyeHeightImpl() const
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        switch (GetDataPoseImpl())
        {
        case Pose::Swimming:
        case Pose::FallFlying:
        case Pose::SpinAttack:
            return 0.4;
        case Pose::Crouching:
            return 1.27;
        default:
            return 1.62;
        }
#else
        return 1.62;
#endif
    }

    double PlayerEntity::GetWidthImpl() const
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        return GetWidth(GetDataPoseImpl());
#else
        return 0.6;
#endif
    }

    double PlayerEntity::GetHeightImpl() const
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        return GetHeight(GetDataPoseImpl());
#else
        return 1.8;
#endif
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    AABB PlayerEntity::GetColliderImpl(const Pose pose) const
    {
        const double half_width = GetWidth(pose) / 2.0;
        const double half_height = GetHeight(pose) / 2.0;
        return AABB(Vector3<double>(position.x, position.y + half_height, position.z), Vector3<double>(half_width, half_height, half_width));
    }
#endif

}
