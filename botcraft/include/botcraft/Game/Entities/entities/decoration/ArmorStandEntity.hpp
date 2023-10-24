#pragma once

#include "botcraft/Game/Entities/entities/LivingEntity.hpp"

namespace Botcraft
{
    class ArmorStandEntity : public LivingEntity
    {
    protected:
        static constexpr int metadata_count = 7;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = LivingEntity::metadata_count + LivingEntity::hierarchy_metadata_count;

    public:
        ArmorStandEntity();
        virtual ~ArmorStandEntity();

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

        char GetDataClientFlags() const;
        Vector3<float> GetDataHeadPose() const;
        Vector3<float> GetDataBodyPose() const;
        Vector3<float> GetDataLeftArmPose() const;
        Vector3<float> GetDataRightArmPose() const;
        Vector3<float> GetDataLeftLegPose() const;
        Vector3<float> GetDataRightLegPose() const;

        void SetDataClientFlags(const char data_client_flags);
        void SetDataHeadPose(const Vector3<float>& data_head_pose);
        void SetDataBodyPose(const Vector3<float>& data_body_pose);
        void SetDataLeftArmPose(const Vector3<float>& data_left_arm_pose);
        void SetDataRightArmPose(const Vector3<float>& data_right_arm_pose);
        void SetDataLeftLegPose(const Vector3<float>& data_left_leg_pose);
        void SetDataRightLegPose(const Vector3<float>& data_right_leg_pose);

    };
}
