#include "botcraft/Game/Entities/Player.hpp"

#define PI 3.14159265359

namespace Botcraft
{
    const Vector3<double> Player::boxSize = Vector3<double>(0.3, 0.9, 0.3);

    Player::Player()
    {
        position = Vector3<double>(0.0, 1000.0, 0.0);

        frontVector = Vector3<double>(0.0, 0.0, 1.0);
        rightVector = Vector3<double>(1.0, 0.0, 0.0);

        flying_speed = 1.0f;
        is_flying = false;
        is_running = false;

        on_ground = true;

        is_invulnerable = false;
        health = 0.0f;
        food = 20;
        food_saturation = 5.0f;

        has_moved = true;
    }

    std::mutex& Player::GetMutex()
    {
        return player_mutex;
    }

    const Vector3<double>& Player::GetFrontVector() const
    {
        return frontVector;
    }

    const Vector3<double>& Player::GetXZVector() const
    {
        return xzVector;
    }

    const Vector3<double>& Player::GetRightVector() const
    {
        return rightVector;
    }

    const AABB Player::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + boxSize.y, position.z), boxSize);
    }

    const float Player::GetFlyingSpeed() const
    {
        return flying_speed;
    }

    const bool Player::GetIsFlying() const
    {
        return is_flying;
    }

    const bool Player::GetIsRunning() const
    {
        return is_running;
    }

    const bool Player::GetIsInvulnerable() const
    {
        return is_invulnerable;
    }

    const float Player::GetHealth() const
    {
        return health;
    }

    const int Player::GetFood() const
    {
        return food;
    }

    const float Player::GetFoodSaturation() const
    {
        return food_saturation;
    }

    const bool Player::GetHasMoved() const
    {
        return has_moved;
    }

    void Player::SetPosition(const Vector3<double>& pos)
    {
        has_moved = position != pos;
        position = pos;
    }

    void Player::SetX(const double x)
    {
        has_moved = position.x != x;
        position.x = x;
    }

    void Player::SetY(const double y)
    {
        has_moved = position.y != y;
        position.y = y;
    }

    void Player::SetZ(const double z)
    {
        has_moved = position.z != z;
        position.z = z;
    }

    void Player::SetYaw(const float yaw_)
    {
        if (yaw != yaw_)
        {
            has_moved = true;
            yaw = yaw_;
            UpdateVectors();
        }
    }

    void Player::SetPitch(const float pitch_)
    {
        if (pitch != pitch_)
        {
            has_moved = true;
            pitch = pitch_;
            UpdateVectors();
        }
    }

    void Player::SetFlyingSpeed(const float s)
    {
        flying_speed = s;
    }

    void Player::SetIsFlying(const bool b)
    {
        is_flying = b;
    }

    void Player::SetIsRunning(const bool b)
    {
        is_running = b;
    }

    void Player::SetIsInvulnerable(const bool b)
    {
        is_invulnerable = b;
    }

    void Player::SetHealth(const float health_)
    {
        health = health_;
    }

    void Player::SetFood(const int food_)
    {
        food = food_;
    }

    void Player::SetFoodSaturation(const float food_saturation_)
    {
        food_saturation = food_saturation_;
    }

    void Player::SetHasMoved(const bool has_moved_)
    {
        has_moved = has_moved_;
    }

    void Player::LookAt(const Vector3<double>& pos, const bool set_pitch)
    {
        Vector3<double> direction = (pos - position);
        direction.Normalize();
        const double new_pitch = asin(direction.y) * 180.0 / PI;
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

    void Player::UpdateVectors()
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