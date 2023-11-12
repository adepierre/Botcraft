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


    double PlayerEntity::GetHeightImpl() const
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        switch (GetDataPoseImpl())
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
#else
        return 1.8;
#endif
    }

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
        switch (GetDataPoseImpl())
        {
        case Pose::Sleeping:
        case Pose::Dying:
            return 0.2;
        default:
            return 0.6;
        }
#else
        return 0.6;
#endif
    }

}
