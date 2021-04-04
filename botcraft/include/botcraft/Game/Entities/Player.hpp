#pragma once

#include <mutex>

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Game/AABB.hpp"
#include "botcraft/Game/Entities/Entity.hpp"

namespace Botcraft 
{
    class Player : public Entity
    {
    public:
        Player();

        std::mutex& GetMutex();

        //Half size of the collider
        static const Vector3<double> boxSize;

        const Vector3<double>& GetFrontVector() const;
        const Vector3<double>& GetXZVector() const;
        const Vector3<double>& GetRightVector() const;
        const AABB GetCollider() const;
        const float GetFlyingSpeed() const;
        const bool GetIsFlying() const;
        const bool GetIsRunning() const;
        const bool GetIsInvulnerable() const;
        const float GetHealth() const;
        const int GetFood() const;
        const float GetFoodSaturation() const;
        const bool GetHasMoved() const;

        virtual void SetPosition(const Vector3<double>& pos) override;
        virtual void SetX(const double x) override;
        virtual void SetY(const double y) override;
        virtual void SetZ(const double z) override;
        virtual void SetYaw(const float yaw_) override;
        virtual void SetPitch(const float pitch_) override;
        void SetFlyingSpeed(const float s);
        void SetIsFlying(const bool b);
        void SetIsRunning(const bool b);
        void SetIsInvulnerable(const bool b);
        void SetHealth(const float health_);
        void SetFood(const int food_);
        void SetFoodSaturation(const float food_saturation_);
        void SetHasMoved(const bool has_moved_);

        void LookAt(const Vector3<double>& pos, const bool set_pitch = false);

    private:
        void UpdateVectors();

    private:
        std::mutex player_mutex;

        Vector3<double> frontVector;
        Vector3<double> xzVector;
        Vector3<double> rightVector;

        float flying_speed;
        bool is_flying;
        bool is_running;

        bool is_invulnerable;
        float health;
        int food;
        float food_saturation;

        bool has_moved;
    };
} // Botcraft