#include "botcraft/Game/Entities/entities/decoration/ArmorStandEntity.hpp"

#include <mutex>

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

        // Initialize all attributes with default values
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 0.0) });
#endif
    }

    ArmorStandEntity::~ArmorStandEntity()
    {

    }


    std::string ArmorStandEntity::GetName() const
    {
        return "armor_stand";
    }

    EntityType ArmorStandEntity::GetType() const
    {
        return EntityType::ArmorStand;
    }


    std::string ArmorStandEntity::GetClassName()
    {
        return "armor_stand";
    }

    EntityType ArmorStandEntity::GetClassType()
    {
        return EntityType::ArmorStand;
    }


    ProtocolCraft::Json::Value ArmorStandEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = LivingEntity::Serialize();

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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char ArmorStandEntity::GetDataClientFlags() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_client_flags"));
    }

    Vector3<float> ArmorStandEntity::GetDataHeadPose() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<Vector3<float>>(metadata.at("data_head_pose"));
    }

    Vector3<float> ArmorStandEntity::GetDataBodyPose() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<Vector3<float>>(metadata.at("data_body_pose"));
    }

    Vector3<float> ArmorStandEntity::GetDataLeftArmPose() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<Vector3<float>>(metadata.at("data_left_arm_pose"));
    }

    Vector3<float> ArmorStandEntity::GetDataRightArmPose() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<Vector3<float>>(metadata.at("data_right_arm_pose"));
    }

    Vector3<float> ArmorStandEntity::GetDataLeftLegPose() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<Vector3<float>>(metadata.at("data_left_leg_pose"));
    }

    Vector3<float> ArmorStandEntity::GetDataRightLegPose() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<Vector3<float>>(metadata.at("data_right_leg_pose"));
    }


    void ArmorStandEntity::SetDataClientFlags(const char data_client_flags)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_client_flags"] = data_client_flags;
    }

    void ArmorStandEntity::SetDataHeadPose(const Vector3<float>& data_head_pose)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_head_pose"] = data_head_pose;
    }

    void ArmorStandEntity::SetDataBodyPose(const Vector3<float>& data_body_pose)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_body_pose"] = data_body_pose;
    }

    void ArmorStandEntity::SetDataLeftArmPose(const Vector3<float>& data_left_arm_pose)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_left_arm_pose"] = data_left_arm_pose;
    }

    void ArmorStandEntity::SetDataRightArmPose(const Vector3<float>& data_right_arm_pose)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_right_arm_pose"] = data_right_arm_pose;
    }

    void ArmorStandEntity::SetDataLeftLegPose(const Vector3<float>& data_left_leg_pose)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_left_leg_pose"] = data_left_leg_pose;
    }

    void ArmorStandEntity::SetDataRightLegPose(const Vector3<float>& data_right_leg_pose)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_right_leg_pose"] = data_right_leg_pose;
    }


    double ArmorStandEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double ArmorStandEntity::GetHeightImpl() const
    {
        return 1.975;
    }

}
