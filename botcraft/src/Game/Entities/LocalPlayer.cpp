#include "botcraft/Game/Entities/LocalPlayer.hpp"

#define PI 3.14159265359

namespace Botcraft
{
    LocalPlayer::LocalPlayer()
    {
        position = Vector3<double>(0.0, 1000.0, 0.0);
        frontVector = Vector3<double>(0.0, 0.0, 1.0);
        rightVector = Vector3<double>(1.0, 0.0, 0.0);

        flying_speed = 1.0f;
        walking_speed = 1.0f;
        is_flying = false;
        is_running = false;

        is_invulnerable = false;
        health = 0.0f;
        food = 20;
        food_saturation = 5.0f;

        has_moved = true;
    }

    LocalPlayer::~LocalPlayer()
    {

    }


    std::mutex& LocalPlayer::GetMutex()
    {
        return player_mutex;
    }


    const Vector3<double>& LocalPlayer::GetFrontVector() const
    {
        return frontVector;
    }

    const Vector3<double>& LocalPlayer::GetXZVector() const
    {
        return xzVector;
    }

    const Vector3<double>& LocalPlayer::GetRightVector() const
    {
        return rightVector;
    }

    const Vector3<double>& LocalPlayer::GetPlayerInputs() const
    {
        return player_inputs;
    }

    const double LocalPlayer::GetPlayerInputsX() const
    {
        return player_inputs.x;
    }

    const double LocalPlayer::GetPlayerInputsY() const
    {
        return player_inputs.y;
    }

    const double LocalPlayer::GetPlayerInputsZ() const
    {
        return player_inputs.z;
    }


    float LocalPlayer::GetFlyingSpeed() const
    {
        return flying_speed;
    }

    float LocalPlayer::GetWalkingSpeed() const
    {
        return walking_speed;
    }

    bool LocalPlayer::GetIsFlying() const
    {
        return is_flying;
    }

    bool LocalPlayer::GetIsRunning() const
    {
        return is_running;
    }

    bool LocalPlayer::GetIsInvulnerable() const
    {
        return is_invulnerable;
    }

    float LocalPlayer::GetHealth() const
    {
        return health;
    }

    int LocalPlayer::GetFood() const
    {
        return food;
    }

    float LocalPlayer::GetFoodSaturation() const
    {
        return food_saturation;
    }

    bool LocalPlayer::GetHasMoved() const
    {
        return has_moved;
    }


    void LocalPlayer::SetFlyingSpeed(const float flying_speed_)
    {
        flying_speed = flying_speed_;
    }

    void LocalPlayer::SetWalkingSpeed(const float walking_speed_)
    {
        walking_speed = walking_speed_;
    }

    void LocalPlayer::SetIsFlying(const bool b)
    {
        is_flying = b;
    }

    void LocalPlayer::SetIsRunning(const bool b)
    {
        is_running = b;
    }

    void LocalPlayer::SetIsInvulnerable(const bool b)
    {
        is_invulnerable = b;
    }

    void LocalPlayer::SetHealth(const float health_)
    {
        health = health_;
    }

    void LocalPlayer::SetFood(const int food_)
    {
        food = food_;
    }

    void LocalPlayer::SetFoodSaturation(const float food_saturation_)
    {
        food_saturation = food_saturation_;
    }

    void LocalPlayer::SetHasMoved(const bool has_moved_)
    {
        has_moved = has_moved_;
    }


    void LocalPlayer::SetPosition(const Vector3<double>& pos)
    {
        has_moved |= position != pos;
        position = pos;
    }

    void LocalPlayer::SetX(const double x)
    {
        has_moved |= position.x != x;
        position.x = x;
    }

    void LocalPlayer::SetY(const double y)
    {
        has_moved |= position.y != y;
        position.y = y;
    }

    void LocalPlayer::SetZ(const double z)
    {
        has_moved |= position.z != z;
        position.z = z;
    }

    void LocalPlayer::SetYaw(const float yaw_)
    {
        if (yaw != yaw_)
        {
            has_moved = true;
            yaw = yaw_;
            UpdateVectors();
        }
    }

    void LocalPlayer::SetPitch(const float pitch_)
    {
        if (pitch != pitch_)
        {
            has_moved = true;
            pitch = pitch_;
            UpdateVectors();
        }
    }

    void LocalPlayer::SetPlayerInputs(const Vector3<double>& p)
    {
        player_inputs = p;
    }

    void LocalPlayer::SetPlayerInputsX(const double x)
    {
        player_inputs.x = x;
    }

    void LocalPlayer::SetPlayerInputsY(const double y)
    {
        player_inputs.y = y;
    }

    void LocalPlayer::SetPlayerInputsZ(const double z)
    {
        player_inputs.z = z;
    }

    void LocalPlayer::AddPlayerInputs(const Vector3<double>& p)
    {
        player_inputs += p;
    }

    void LocalPlayer::AddPlayerInputsX(const double x)
    {
        player_inputs.x += x;
    }

    void LocalPlayer::AddPlayerInputsY(const double y)
    {
        player_inputs.y += y;
    }

    void LocalPlayer::AddPlayerInputsZ(const double z)
    {
        player_inputs.z += z;
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
        Vector3<double> direction = (pos - position);
        // We want to set the orientation from the eyes, not the feet
        direction.y -= 1.62;
        direction.Normalize();
        const double new_pitch = -asin(direction.y) * 180.0 / PI;
        double new_yaw = -atan2(direction.x, direction.z) * 180.0 / PI;
        if (new_yaw < 0)
        {
            new_yaw += 360;
        }
        if (new_yaw != yaw ||
            (set_pitch && new_pitch != pitch))
        {
            if (set_pitch)
            {
                pitch = new_pitch;
            }
            yaw = new_yaw;
            has_moved = true;
            UpdateVectors();
        }
    }

    void LocalPlayer::Jump()
    {
        if (!on_ground)
        {
            return;
        }
        SetSpeedY(0.42);
    }

    void LocalPlayer::UpdateVectors()
    {
        const double rad_yaw = yaw * PI / 180.0;
        const double rad_pitch = pitch * PI / 180.0;
        frontVector = Vector3<double>(-sin(rad_yaw) * cos(rad_pitch), -sin(rad_pitch), cos(rad_yaw) * cos(rad_pitch));

        frontVector.Normalize();

        xzVector = frontVector;
        xzVector.y = 0.0;
        xzVector.Normalize();

        //Right = crossproduct(front, (0, 1.0, 0))
        double norm = sqrt(frontVector.x * frontVector.x + frontVector.z * frontVector.z);
        rightVector = Vector3<double>(-frontVector.z / norm, 0.0, frontVector.x / norm);
    }
} //Botcraft
