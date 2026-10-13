#include "botcraft/Game/Entities/entities/player/PlayerEntity.hpp"

namespace Botcraft
{
    PlayerEntity::PlayerEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataPlayerAbsorptionId(0.0f);
        SetDataScoreId(0);
#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
        SetDataPlayerModeCustomisation(0);
        SetDataPlayerMainHand(1);
        SetDataShoulderLeft(ProtocolCraft::NBT::Value());
        SetDataShoulderRight(ProtocolCraft::NBT::Value());
#else
        SetDataShoulderParrotLeft(std::nullopt);
        SetDataShoulderParrotRight(std::nullopt);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 1.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.1) });
        attributes.insert({ EntityAttribute::Type::AttackSpeed, EntityAttribute(EntityAttribute::Type::AttackSpeed, 4.0) });
        attributes.insert({ EntityAttribute::Type::Luck, EntityAttribute(EntityAttribute::Type::Luck, 0.0) });
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        attributes.insert({ EntityAttribute::Type::PlayerBlockInteractionRange, EntityAttribute(EntityAttribute::Type::PlayerBlockInteractionRange, 4.5) });
#if PROTOCOL_VERSION < 775 /* < 26.1 */
        attributes.insert({ EntityAttribute::Type::EntityInteractionRange, EntityAttribute(EntityAttribute::Type::EntityInteractionRange, 3.0) });
#endif
        attributes.insert({ EntityAttribute::Type::PlayerBlockBreakSpeed, EntityAttribute(EntityAttribute::Type::PlayerBlockBreakSpeed, 1.0) });
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        attributes.insert({ EntityAttribute::Type::PlayerSubmergedMiningSpeed, EntityAttribute(EntityAttribute::Type::PlayerSubmergedMiningSpeed, 0.2) });
        attributes.insert({ EntityAttribute::Type::PlayerSneakingSpeed, EntityAttribute(EntityAttribute::Type::PlayerSneakingSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::PlayerMiningEfficiency, EntityAttribute(EntityAttribute::Type::PlayerMiningEfficiency, 0.0) });
        attributes.insert({ EntityAttribute::Type::PlayerSweepingDamageRatio, EntityAttribute(EntityAttribute::Type::PlayerSweepingDamageRatio, 0.0) });
#endif
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        attributes.insert({ EntityAttribute::Type::WaypointTransmitRange, EntityAttribute(EntityAttribute::Type::WaypointTransmitRange, 6.0) });
        attributes.insert({ EntityAttribute::Type::WaypointReceiveRange, EntityAttribute(EntityAttribute::Type::WaypointReceiveRange, 6.0) });
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
#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
        output["metadata"]["data_player_mode_customisation"] = GetDataPlayerModeCustomisation();
        output["metadata"]["data_player_main_hand"] = GetDataPlayerMainHand();
        output["metadata"]["data_shoulder_left"] = GetDataShoulderLeft().Serialize();
        output["metadata"]["data_shoulder_right"] = GetDataShoulderRight().Serialize();
#else
        const std::optional<int> data_shoulder_parrot_left = GetDataShoulderParrotLeft();
        output["metadata"]["data_shoulder_parrot_left"] = data_shoulder_parrot_left.has_value() ? ProtocolCraft::Json::Value(data_shoulder_parrot_left.value()) : nullptr;
        const std::optional<int> data_shoulder_parrot_right = GetDataShoulderParrotRight();
        output["metadata"]["data_shoulder_parrot_right"] = data_shoulder_parrot_right.has_value() ? ProtocolCraft::Json::Value(data_shoulder_parrot_right.value()) : nullptr;
#endif

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();
        output["attributes"]["attack_speed"] = GetAttributeAttackSpeedValue();
        output["attributes"]["luck"] = GetAttributeLuckValue();
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        output["attributes"]["block_interaction_range"] = GetAttributePlayerBlockInteractionRangeValue();
#if PROTOCOL_VERSION < 775 /* < 26.1 */
        output["attributes"]["entity_interaction_range"] = GetAttributeEntityInteractionRangeValue();
#endif
        output["attributes"]["block_break_speed"] = GetAttributePlayerBlockBreakSpeedValue();
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        output["attributes"]["submerged_mining_speed"] = GetAttributePlayerSubmergedMiningSpeedValue();
        output["attributes"]["sneaking_speed"] = GetAttributePlayerSneakingSpeedValue();
        output["attributes"]["mining_efficiency"] = GetAttributePlayerMiningEfficiencyValue();
        output["attributes"]["sweeping_damage_ratio"] = GetAttributePlayerSweepingDamageRatioValue();
#endif
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        output["attributes"]["waypoint_receive_range"] = GetAttributeWaypointReceiveRangeValue();
#endif

        return output;
    }


    float PlayerEntity::GetDataPlayerAbsorptionId() const
    {
        return GetMetadata<float>(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_absorption_id"));
    }

    int PlayerEntity::GetDataScoreId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_score_id"));
    }

#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
    char PlayerEntity::GetDataPlayerModeCustomisation() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_mode_customisation"));
    }

    char PlayerEntity::GetDataPlayerMainHand() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_main_hand"));
    }

    ProtocolCraft::NBT::Value PlayerEntity::GetDataShoulderLeft() const
    {
        return GetMetadata<ProtocolCraft::NBT::Value>(BOTCRAFT_ENTITY_METADATA_INDEX("data_shoulder_left"));
    }

    ProtocolCraft::NBT::Value PlayerEntity::GetDataShoulderRight() const
    {
        return GetMetadata<ProtocolCraft::NBT::Value>(BOTCRAFT_ENTITY_METADATA_INDEX("data_shoulder_right"));
    }
#else
    std::optional<int> PlayerEntity::GetDataShoulderParrotLeft() const
    {
        return GetMetadata<std::optional<int>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_shoulder_parrot_left"));
    }

    std::optional<int> PlayerEntity::GetDataShoulderParrotRight() const
    {
        return GetMetadata<std::optional<int>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_shoulder_parrot_right"));
    }
#endif


    void PlayerEntity::SetDataPlayerAbsorptionId(const float data_player_absorption_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_absorption_id"), data_player_absorption_id);
    }

    void PlayerEntity::SetDataScoreId(const int data_score_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_score_id"), data_score_id);
    }

#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
    void PlayerEntity::SetDataPlayerModeCustomisation(const char data_player_mode_customisation)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_mode_customisation"), data_player_mode_customisation);
    }

    void PlayerEntity::SetDataPlayerMainHand(const char data_player_main_hand)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_main_hand"), data_player_main_hand);
    }

    void PlayerEntity::SetDataShoulderLeft(const ProtocolCraft::NBT::Value& data_shoulder_left)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_shoulder_left"), data_shoulder_left);
    }

    void PlayerEntity::SetDataShoulderRight(const ProtocolCraft::NBT::Value& data_shoulder_right)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_shoulder_right"), data_shoulder_right);
    }
#else
    void PlayerEntity::SetDataShoulderParrotLeft(const std::optional<int>& data_shoulder_parrot_left)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_shoulder_parrot_left"), data_shoulder_parrot_left);
    }

    void PlayerEntity::SetDataShoulderParrotRight(const std::optional<int>& data_shoulder_parrot_right)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_shoulder_parrot_right"), data_shoulder_parrot_right);
    }
#endif

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

#if PROTOCOL_VERSION < 775 /* < 26.1 */
    double PlayerEntity::GetAttributeEntityInteractionRangeValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::EntityInteractionRange).GetValue();
    }
#endif

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

#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
    double PlayerEntity::GetAttributeWaypointReceiveRangeValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::WaypointReceiveRange).GetValue();
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
        const float half_width = static_cast<float>(GetWidth(pose)) / 2.0f;
        const float half_height = static_cast<float>(GetHeight(pose)) / 2.0f;
        return AABB(
            Vector3<double>(position.x, position.y + half_height, position.z), Vector3<double>(half_width, half_height, half_width));
    }
#endif

}
