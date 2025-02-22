#pragma once

#include "botcraft/Game/Entities/entities/player/PlayerEntity.hpp"

#include <optional>

namespace Botcraft
{
    struct PlayerInputs
    {
        float forward_axis = 0.0f;
        float left_axis = 0.0f;
        bool jump = false;
        bool sneak = false;
        bool sprint = false;
    };

    class LocalPlayer : public PlayerEntity
    {
        friend class PhysicsManager;

    public:
        LocalPlayer();
        virtual ~LocalPlayer();


        Vector3<double> GetFrontVector() const;
        Vector3<double> GetXZVector() const;
        Vector3<double> GetRightVector() const;

        GameType GetGameMode() const;
        char GetAbilitiesFlags() const;
        bool GetInvulnerable() const;
        bool GetFlying() const;
        bool GetMayFly() const;
        /// @brief If true, the player can break any block in no time (creative mode)
        /// @return Instabuild ability value
        bool GetInstabuild() const;
        bool GetMayBuild() const;
        float GetFlyingSpeed() const;
        float GetWalkingSpeed() const;
        float GetHealth() const;
        int GetFood() const;
        float GetFoodSaturation() const;
        bool GetDirtyInputs() const;
        bool IsClimbing() const;
        bool IsInWater() const;
        bool IsInLava() const;
        bool IsInFluid() const;

        void SetGameMode(const GameType game_mode_);
        void SetAbilitiesFlags(const char abilities_flags_);
        void SetFlyingSpeed(const float flying_speed_);
        void SetWalkingSpeed(const float walking_speed_);
        void SetHealth(const float health_);
        void SetFood(const int food_);
        void SetFoodSaturation(const float food_saturation_);
        void SetDirtyInputs();

        virtual void SetPosition(const Vector3<double>& pos) override;
        virtual void SetX(const double x) override;
        virtual void SetY(const double y) override;
        virtual void SetZ(const double z) override;
        /// @brief Set Yaw angle (horizontal plane orientation)
        /// @param yaw_ New yaw, in degree
        virtual void SetYaw(const float yaw_) override;
        /// @brief Set Pitch angle (look up is -90°, look down is 90°)
        /// @param pitch_ New pitch, in degree
        virtual void SetPitch(const float pitch_) override;

        void SetInputsForward(const float f);
        void AddInputsForward(const float f);
        void SetInputsLeft(const float f);
        void AddInputsLeft(const float f);
        void SetInputsJump(const bool b);
        void SetInputsSneak(const bool b);
        void SetInputsSprint(const bool b);
        void SetInputs(const PlayerInputs& inputs_);

        virtual bool IsLocalPlayer() const override;
        virtual bool IsRemotePlayer() const override;

        void LookAt(const Vector3<double>& pos, const bool set_pitch = false);

    private:
        void UpdateVectors();
        void ResetInputs();
        void SetAbilitiesFlagsImpl(const char abilities_flags_);
        void UpdateAbilitiesFlagsImpl();

#if PROTOCOL_VERSION < 405 /* < 1.14 */
    protected:
        virtual double GetEyeHeightImpl() const override;
        virtual double GetHeightImpl() const override;
#endif

    private:
        Vector3<double> front_vector;
        Vector3<double> xz_vector;
        Vector3<double> right_vector;

        PlayerInputs inputs;
        bool dirty_inputs;

        GameType game_mode;

        char abilities_flags;
        bool invulnerable;
        /// @brief Flying in creative/spectator
        bool flying;
        /// @brief If this player can fly in creative/spectator
        bool may_fly;
        /// @brief Insta break blocks in creative
        bool instabuild;
        bool may_build;
        float flying_speed;
        float walking_speed;

        float health;
        int food;
        float food_saturation;

        // Used during physics step (accessible as PhysicsManager is a friend class)
        bool in_water;
        bool in_lava;
        bool under_water;
        bool crouching;
        bool horizontal_collision;
        bool on_climbable;
        Vector3<double> stuck_speed_multiplier;
        int jump_delay;
        int fly_jump_trigger_time;
        int sprint_double_tap_trigger_time;
        std::optional<Position> supporting_block_pos;
        bool on_ground_without_supporting_block;

        bool previous_sprinting;
        bool previous_shift_key_down;
        Vector3<double> previous_position;
        float previous_yaw;
        float previous_pitch;
        bool previous_on_ground;
        bool previous_jump;
        bool previous_sneak;
        float previous_forward;
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        bool previous_horizontal_collision;
        PlayerInputs last_sent_inputs;
#endif
    };
} // Botcraft
