#pragma once

#include <mutex>

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Game/AABB.hpp"

namespace Botcraft 
{
    class Player
    {
    public:
        Player();

        std::mutex& GetMutex();

        //Half size of the collider
        static const Vector3<double> boxSize;

        const Vector3<double>& GetPosition() const;
        const Vector3<double>& GetFrontVector() const;
        const Vector3<double>& GetXZVector() const;
        const Vector3<double>& GetRightVector() const;
        const AABB GetCollider() const;
        const float GetYaw() const;
        const float GetPitch() const;
        const Vector3<double> &GetSpeed() const;
        const float GetFlyingSpeed() const;
        const bool GetIsFlying() const;
        const bool GetIsRunning() const;
        const int GetEID() const;
        const bool GetOnGround() const;
        const bool GetIsInvulnerable() const;
        const float GetHealth() const;
        const int GetFood() const;
        const float GetFoodSaturation() const;

        void SetX(const double x);
        void SetY(const double y);
        void SetZ(const double z);
        void SetPosition(const Vector3<double> &pos);
        void SetYaw(const float yaw_);
        void SetPitch(const float pitch_);
        void SetSpeed(const Vector3<double> &speed_);
        void SetSpeedX(const double speed_x);
        void SetSpeedY(const double speed_y);
        void SetSpeedZ(const double speed_z);
        void SetFlyingSpeed(const float s);
        void SetIsFlying(const bool b);
        void SetIsRunning(const bool b);
        void SetEID(const int eid_);
        void SetOnGround(const bool on_ground_);
        void SetIsInvulnerable(const bool b);
        void SetHealth(const float health_);
        void SetFood(const int food_);
        void SetFoodSaturation(const float food_saturation_);

    private:
        void UpdateVectors();

    private:
        std::mutex player_mutex;

        int eid;

        Vector3<double> position;

        float yaw;
        float pitch;

        Vector3<double> frontVector;
        Vector3<double> xzVector;
        Vector3<double> rightVector;

        Vector3<double> speed;

        float flying_speed;
        bool is_flying;
        bool is_running;

        bool on_ground;

        bool is_invulnerable;
        float health;
        int food;
        float food_saturation;
    };
} // Botcraft