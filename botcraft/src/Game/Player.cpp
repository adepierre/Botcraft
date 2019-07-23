#include "botcraft/Game/Player.hpp"

#define PI 3.14159265359

namespace Botcraft
{
    const Vector3<double> Player::boxSize = Vector3<double>(0.3, 0.9, 0.3);

    Player::Player()
    {
        position = Vector3<double>(0.0, 1000.0, 0.0);

        yaw = 0.0f;
        pitch = 0.0f;

        frontVector = Vector3<double>(0.0, 0.0, 1.0);
        rightVector = Vector3<double>(1.0, 0.0, 0.0);

        flying_speed = 1.0f;
        is_flying = false;
        is_running = false;

        speed = Vector3<double>(0.0, 0.0, 0.0);
        on_ground = true;

        eid = 0;

        is_invulnerable = false;
        health = 0.0f;
        food = 20;
        food_saturation = 5.0f;
    }

    const Vector3<double>& Player::GetPosition() const
    {
        return position;
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

    const float Player::GetYaw() const
    {
        return yaw;
    }

    const float Player::GetPitch() const
    {
        return pitch;
    }

    const Vector3<double> &Player::GetSpeed() const
    {
        return speed;
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

    const int Player::GetEID() const
    {
        return eid;
    }

    const bool Player::GetOnGround() const
    {
        return on_ground;
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

    void Player::SetX(const double x)
    {
        position.x = x;
    }

    void Player::SetY(const double y)
    {
        position.y = y;
    }

    void Player::SetZ(const double z)
    {
        position.z = z;
    }

    void Player::SetPosition(const Vector3<double> &pos)
    {
        position = pos;
    }

    void Player::SetYaw(const float yaw_)
    {
        yaw = yaw_;
        UpdateVectors();
    }

    void Player::SetPitch(const float pitch_)
    {
        pitch = pitch_;
        UpdateVectors();
    }

    void Player::SetSpeed(const Vector3<double> &speed_)
    {
        speed = speed_;
    }

    void Player::SetSpeedX(const double speed_x)
    {
        speed.x = speed_x;
    }

    void Player::SetSpeedY(const double speed_y)
    {
        speed.y = speed_y;
    }

    void Player::SetSpeedZ(const double speed_z)
    {
        speed.z = speed_z;
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

    void Player::SetEID(const int eid_)
    {
        eid = eid_;
    }

    void Player::SetOnGround(const bool on_ground_)
    {
        on_ground = on_ground_;
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

    void Player::UpdateVectors()
    {
        double rad_yaw = yaw * PI / 180.0;
        double rad_pitch = pitch * PI / 180.0;
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