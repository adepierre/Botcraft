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
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

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

    };
}
