#pragma once

#include "botcraft/Game/Entities/entities/LivingEntity.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace Botcraft
{
    class PlayerEntity : public LivingEntity
    {
    protected:
        static constexpr int metadata_count = 6;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = LivingEntity::metadata_count + LivingEntity::hierarchy_metadata_count;

    public:
        PlayerEntity();
        virtual ~PlayerEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        using Entity::GetCollider; // Required as otherwise GetCollider(Pose) would be found and stop the search for a GetCollider match
        AABB GetCollider(const Pose pose) const;
        using Entity::GetHeight; // Required as otherwise GetHeight(Pose) would be found and stop the search for a GetHeight match
        double GetHeight(const Pose pose) const;
        using Entity::GetWidth; // Required as otherwise GetWidth(Pose) would be found and stop the search for a GetWidth match
        double GetWidth(const Pose pose) const;
#endif
        double GetEyeHeight() const;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        float GetDataPlayerAbsorptionId() const;
        int GetDataScoreId() const;
        char GetDataPlayerModeCustomisation() const;
        char GetDataPlayerMainHand() const;
        ProtocolCraft::NBT::Value GetDataShoulderLeft() const;
        ProtocolCraft::NBT::Value GetDataShoulderRight() const;

        void SetDataPlayerAbsorptionId(const float data_player_absorption_id);
        void SetDataScoreId(const int data_score_id);
        void SetDataPlayerModeCustomisation(const char data_player_mode_customisation);
        void SetDataPlayerMainHand(const char data_player_main_hand);
        void SetDataShoulderLeft(const ProtocolCraft::NBT::Value& data_shoulder_left);
        void SetDataShoulderRight(const ProtocolCraft::NBT::Value& data_shoulder_right);

        virtual bool IsRemotePlayer() const override;

        // Attribute stuff
        double GetAttributeAttackDamageValue() const;
        double GetAttributeAttackSpeedValue() const;
        double GetAttributeLuckValue() const;

    protected:
        double GetEyeHeightImpl() const;
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        using Entity::GetColliderImpl; // Required as otherwise GetColliderImpl(Pose) would be found and stop the search for a GetColliderImpl match
        AABB GetColliderImpl(const Pose pose) const;
#endif

    };
}
