#include "botcraft/Game/Entities/LocalPlayer.hpp"

#include <limits>
#include <mutex>

namespace Botcraft
{
    LocalPlayer::LocalPlayer()
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);

        position = Vector3<double>(0.0, std::numeric_limits<double>::quiet_NaN(), 0.0);
        front_vector = Vector3<double>(0.0, 0.0, 1.0);
        right_vector = Vector3<double>(1.0, 0.0, 0.0);

        inputs = PlayerInputs();
        dirty_inputs = false;

        game_mode = GameType::None;

        invulnerable = false;
        flying = false;
        may_fly = false;
        instabuild = false;
        may_build = true;
        UpdateAbilitiesFlagsImpl();
        flying_speed = 0.05f;
        walking_speed = 0.1f;

        health = 0.0f;
        food = 20;
        food_saturation = 5.0f;

        in_water = false;
        in_lava = false;
        under_water = false;
        crouching = false;
        horizontal_collision = false;
        on_climbable = false;
        stuck_speed_multiplier = Vector3<double>(0.0, 0.0, 0.0);
        jump_delay = 0;
        fly_jump_trigger_time = 0;
        sprint_double_tap_trigger_time = 0;
        supporting_block_pos = std::optional<Position>();
        on_ground_without_supporting_block = false;

        previous_sprinting = false;
        previous_shift_key_down = false;
        previous_position = Vector3<double>(0.0, 0.0, 0.0);
        previous_yaw = 0.0f;
        previous_pitch = 0.0f;
        previous_on_ground = false;
        previous_jump = false;
        previous_sneak = false;
        previous_forward = 0.0f;
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        previous_horizontal_collision = false;
        last_sent_inputs = PlayerInputs();
#endif
    }

    LocalPlayer::~LocalPlayer()
    {

    }


    Vector3<double> LocalPlayer::GetFrontVector() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return front_vector;
    }

    Vector3<double> LocalPlayer::GetXZVector() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return xz_vector;
    }

    Vector3<double> LocalPlayer::GetRightVector() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return right_vector;
    }


    GameType LocalPlayer::GetGameMode() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return game_mode;
    }

    char LocalPlayer::GetAbilitiesFlags() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return abilities_flags;
    }

    bool LocalPlayer::GetInvulnerable() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return invulnerable;
    }

    bool LocalPlayer::GetFlying() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return flying;
    }

    bool LocalPlayer::GetMayFly() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return may_fly;
    }

    bool LocalPlayer::GetInstabuild() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return instabuild;
    }

    bool LocalPlayer::GetMayBuild() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return may_build;
    }

    float LocalPlayer::GetFlyingSpeed() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return flying_speed;
    }

    float LocalPlayer::GetWalkingSpeed() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return walking_speed;
    }

    float LocalPlayer::GetHealth() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return health;
    }

    int LocalPlayer::GetFood() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return food;
    }

    float LocalPlayer::GetFoodSaturation() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return food_saturation;
    }

    bool LocalPlayer::GetDirtyInputs() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return dirty_inputs;
    }

    bool LocalPlayer::IsClimbing() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return on_climbable;
    }

    bool LocalPlayer::IsInWater() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return in_water;
    }

    bool LocalPlayer::IsInLava() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return in_lava;
    }

    bool LocalPlayer::IsInFluid() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return in_lava || in_water;
    }


    void LocalPlayer::SetGameMode(const GameType game_mode_)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        game_mode = game_mode_;
    }

    void LocalPlayer::SetAbilitiesFlags(const char abilities_flags_)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        SetAbilitiesFlagsImpl(abilities_flags_);
    }

    void LocalPlayer::SetFlyingSpeed(const float flying_speed_)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        flying_speed = flying_speed_;
    }

    void LocalPlayer::SetWalkingSpeed(const float walking_speed_)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        walking_speed = walking_speed_;
    }

    void LocalPlayer::SetHealth(const float health_)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        health = health_;
    }

    void LocalPlayer::SetFood(const int food_)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        food = food_;
    }

    void LocalPlayer::SetFoodSaturation(const float food_saturation_)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        food_saturation = food_saturation_;
    }

    void LocalPlayer::SetDirtyInputs()
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        dirty_inputs = true;
    }


    void LocalPlayer::SetPosition(const Vector3<double>& pos)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        position = pos;
    }

    void LocalPlayer::SetX(const double x)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        position.x = x;
    }

    void LocalPlayer::SetY(const double y)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        position.y = y;
    }

    void LocalPlayer::SetZ(const double z)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        position.z = z;
    }

    void LocalPlayer::SetYaw(const float yaw_)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        if (yaw != yaw_)
        {
            yaw = yaw_;
            UpdateVectors();
        }
    }

    void LocalPlayer::SetPitch(const float pitch_)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        if (pitch != pitch_)
        {
            pitch = pitch_;
            UpdateVectors();
        }
    }

    void LocalPlayer::SetInputsForward(const float f)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        inputs.forward_axis = std::clamp(f, -1.0f, 1.0f);
        dirty_inputs = true;
    }

    void LocalPlayer::AddInputsForward(const float f)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        inputs.forward_axis = std::clamp(inputs.forward_axis + f, -1.0f, 1.0f);
        dirty_inputs = true;
    }

    void LocalPlayer::SetInputsLeft(const float f)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        inputs.left_axis = std::clamp(f, -1.0f, 1.0f);
        dirty_inputs = true;
    }

    void LocalPlayer::AddInputsLeft(const float f)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        inputs.left_axis = std::clamp(inputs.left_axis + f, -1.0f, 1.0f);
        dirty_inputs = true;
    }

    void LocalPlayer::SetInputsJump(const bool b)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        inputs.jump = b;
        dirty_inputs = true;
    }

    void LocalPlayer::SetInputsSneak(const bool b)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        inputs.sneak = b;
        dirty_inputs = true;
    }

    void LocalPlayer::SetInputsSprint(const bool b)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        inputs.sprint = b;
        dirty_inputs = true;
    }

    void LocalPlayer::SetInputs(const PlayerInputs& inputs_)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        inputs = inputs_;
        dirty_inputs = true;
    }

    bool LocalPlayer::IsLocalPlayer() const
    {
        return true;
    }

    bool LocalPlayer::IsRemotePlayer() const
    {
        return false;
    }

    void LocalPlayer::LookAt(const Vector3<double>& pos, const bool set_pitch)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        Vector3<double> direction = (pos - position);
        // We want to set the orientation from the eyes, not the feet
        direction.y -= GetEyeHeightImpl();
        direction.Normalize();
        const float new_pitch = static_cast<float>(-std::asin(direction.y) * 57.29577951308232 /* 180/PI */);
        float new_yaw = static_cast<float>(-std::atan2(direction.x, direction.z) * 57.29577951308232 /* 180/PI */);
        if (new_yaw < 0)
        {
            new_yaw += 360.0f;
        }
        if (new_yaw != yaw ||
            (set_pitch && new_pitch != pitch))
        {
            if (set_pitch)
            {
                pitch = new_pitch;
            }
            yaw = new_yaw;
            UpdateVectors();
        }
    }

    void LocalPlayer::UpdateVectors()
    {
        const float rad_yaw = yaw * 0.017453292f /* PI/180 */;
        const float rad_pitch = pitch * 0.017453292f /* PI/180 */;
        const float cos_pitch = std::cos(rad_pitch);
        front_vector = Vector3<double>(-std::sin(rad_yaw) * cos_pitch, -std::sin(rad_pitch), std::cos(rad_yaw) * cos_pitch);

        // Vector is already normalized as front_vector² = (cos²(rad_yaw) + sin²(rad_yaw)) * cos²(rad_pitch) + sin²(rad_pitch) = 1
        // front_vector.Normalize();

        xz_vector = front_vector;
        xz_vector.y = 0.0;
        // xzVector.Norm() = sqrt((cos²(rad_yaw) + sin²(rad_yaw)) * cos²(rad_pitch)) = sqrt(cos²(rad_pitch)) = cos(rad_pitch)
        // xzVector.Normalize();
        xz_vector = xz_vector / cos_pitch;

        //Right = crossproduct(front, (0, 1.0, 0)).Normalize()
        right_vector = Vector3<double>(-front_vector.z / cos_pitch, 0.0, front_vector.x / cos_pitch);
    }

    void LocalPlayer::ResetInputs()
    {
        inputs.forward_axis = 0.0f;
        inputs.left_axis = 0.0f;
        inputs.jump = false;
        inputs.sneak = false;
        inputs.sprint = false;
        dirty_inputs = false;
    }

    void LocalPlayer::SetAbilitiesFlagsImpl(const char abilities_flags_)
    {
        abilities_flags = abilities_flags_;
        invulnerable = abilities_flags & 0x01;
        flying = abilities_flags & 0x02;
        may_fly = abilities_flags & 0x04;
        instabuild = abilities_flags & 0x08;
        may_build = abilities_flags & 0x10;
    }

    void LocalPlayer::UpdateAbilitiesFlagsImpl()
    {
        abilities_flags =
            (invulnerable << 0) |
            (flying << 1) |
            (may_fly << 2) |
            (instabuild << 3) |
            (may_build << 4);
    }

#if PROTOCOL_VERSION < 405 /* < 1.14 */
    double LocalPlayer::GetEyeHeightImpl() const
    {
        return crouching ? 1.5575 : 1.62;
    }

    double LocalPlayer::GetHeightImpl() const
    {
        return crouching ? 1.65 : 1.8;
    }
#endif

} //Botcraft
