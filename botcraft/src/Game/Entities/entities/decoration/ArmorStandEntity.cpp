#include "botcraft/Game/Entities/entities/decoration/ArmorStandEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, ArmorStandEntity::metadata_count> ArmorStandEntity::metadata_names{ {
        "data_client_flags",
        "data_head_pose",
        "data_body_pose",
        "data_left_arm_pose",
        "data_right_arm_pose",
        "data_left_leg_pose",
        "data_right_leg_pose",
    } };

    ArmorStandEntity::ArmorStandEntity()
    {
        // Initialize all metadata with default values
        SetDataClientFlags(0);
        SetDataHeadPose(Vector3<float>(0.0f, 0.0f, 0.0f));
        SetDataBodyPose(Vector3<float>(0.0f, 0.0f, 0.0f));
        SetDataLeftArmPose(Vector3<float>(-10.0f, 0.0f, -10.0f));
        SetDataRightArmPose(Vector3<float>(-15.0f, 0.0f, 10.0f));
        SetDataLeftLegPose(Vector3<float>(-1.0f, 0.0f, -1.0f));
        SetDataRightLegPose(Vector3<float>(1.0f, 0.0f, 1.0f));
    }

    ArmorStandEntity::~ArmorStandEntity()
    {

    }


    std::string ArmorStandEntity::GetName() const
    {
        return "ArmorStand";
    }

    EntityType ArmorStandEntity::GetType() const
    {
        return EntityType::ArmorStand;
    }

    AABB ArmorStandEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double ArmorStandEntity::GetWidth() const
    {
        return 0.5;
    }

    double ArmorStandEntity::GetHeight() const
    {
        return 1.975;
    }


    std::string ArmorStandEntity::GetClassName()
    {
        return "ArmorStand";
    }

    EntityType ArmorStandEntity::GetClassType()
    {
        return EntityType::ArmorStand;
    }


    nlohmann::json ArmorStandEntity::Serialize() const
    {
        nlohmann::json output = LivingEntity::Serialize();

        output["metadata"]["data_client_flags"] = GetDataClientFlags();
        output["metadata"]["data_head_pose"] = GetDataHeadPose().Serialize();
        output["metadata"]["data_body_pose"] = GetDataBodyPose().Serialize();
        output["metadata"]["data_left_arm_pose"] = GetDataLeftArmPose().Serialize();
        output["metadata"]["data_right_arm_pose"] = GetDataRightArmPose().Serialize();
        output["metadata"]["data_left_leg_pose"] = GetDataLeftLegPose().Serialize();
        output["metadata"]["data_right_leg_pose"] = GetDataRightLegPose().Serialize();

        return output;
    }


    void ArmorStandEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            LivingEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char ArmorStandEntity::GetDataClientFlags() const
    {
        return std::any_cast<char>(metadata.at("data_client_flags"));
    }

    const Vector3<float>& ArmorStandEntity::GetDataHeadPose() const
    {
        return std::any_cast<const Vector3<float>&>(metadata.at("data_head_pose"));
    }

    const Vector3<float>& ArmorStandEntity::GetDataBodyPose() const
    {
        return std::any_cast<const Vector3<float>&>(metadata.at("data_body_pose"));
    }

    const Vector3<float>& ArmorStandEntity::GetDataLeftArmPose() const
    {
        return std::any_cast<const Vector3<float>&>(metadata.at("data_left_arm_pose"));
    }

    const Vector3<float>& ArmorStandEntity::GetDataRightArmPose() const
    {
        return std::any_cast<const Vector3<float>&>(metadata.at("data_right_arm_pose"));
    }

    const Vector3<float>& ArmorStandEntity::GetDataLeftLegPose() const
    {
        return std::any_cast<const Vector3<float>&>(metadata.at("data_left_leg_pose"));
    }

    const Vector3<float>& ArmorStandEntity::GetDataRightLegPose() const
    {
        return std::any_cast<const Vector3<float>&>(metadata.at("data_right_leg_pose"));
    }


    void ArmorStandEntity::SetDataClientFlags(const char data_client_flags)
    {
        metadata["data_client_flags"] = data_client_flags;
    }

    void ArmorStandEntity::SetDataHeadPose(const Vector3<float>& data_head_pose)
    {
        metadata["data_head_pose"] = data_head_pose;
    }

    void ArmorStandEntity::SetDataBodyPose(const Vector3<float>& data_body_pose)
    {
        metadata["data_body_pose"] = data_body_pose;
    }

    void ArmorStandEntity::SetDataLeftArmPose(const Vector3<float>& data_left_arm_pose)
    {
        metadata["data_left_arm_pose"] = data_left_arm_pose;
    }

    void ArmorStandEntity::SetDataRightArmPose(const Vector3<float>& data_right_arm_pose)
    {
        metadata["data_right_arm_pose"] = data_right_arm_pose;
    }

    void ArmorStandEntity::SetDataLeftLegPose(const Vector3<float>& data_left_leg_pose)
    {
        metadata["data_left_leg_pose"] = data_left_leg_pose;
    }

    void ArmorStandEntity::SetDataRightLegPose(const Vector3<float>& data_right_leg_pose)
    {
        metadata["data_right_leg_pose"] = data_right_leg_pose;
    }

}
