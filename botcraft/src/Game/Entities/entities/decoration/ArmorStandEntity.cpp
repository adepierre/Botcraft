#include "botcraft/Game/Entities/entities/decoration/ArmorStandEntity.hpp"

namespace Botcraft
{
    ArmorStandEntity::ArmorStandEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    char ArmorStandEntity::GetDataClientFlags() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_client_flags"));
    }

    Vector3<float> ArmorStandEntity::GetDataHeadPose() const
    {
        return GetMetadata<Vector3<float>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_head_pose"));
    }

    Vector3<float> ArmorStandEntity::GetDataBodyPose() const
    {
        return GetMetadata<Vector3<float>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_body_pose"));
    }

    Vector3<float> ArmorStandEntity::GetDataLeftArmPose() const
    {
        return GetMetadata<Vector3<float>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_left_arm_pose"));
    }

    Vector3<float> ArmorStandEntity::GetDataRightArmPose() const
    {
        return GetMetadata<Vector3<float>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_right_arm_pose"));
    }

    Vector3<float> ArmorStandEntity::GetDataLeftLegPose() const
    {
        return GetMetadata<Vector3<float>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_left_leg_pose"));
    }

    Vector3<float> ArmorStandEntity::GetDataRightLegPose() const
    {
        return GetMetadata<Vector3<float>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_right_leg_pose"));
    }


    void ArmorStandEntity::SetDataClientFlags(const char data_client_flags)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_client_flags"), data_client_flags);
    }

    void ArmorStandEntity::SetDataHeadPose(const Vector3<float>& data_head_pose)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_head_pose"), data_head_pose);
    }

    void ArmorStandEntity::SetDataBodyPose(const Vector3<float>& data_body_pose)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_body_pose"), data_body_pose);
    }

    void ArmorStandEntity::SetDataLeftArmPose(const Vector3<float>& data_left_arm_pose)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_left_arm_pose"), data_left_arm_pose);
    }

    void ArmorStandEntity::SetDataRightArmPose(const Vector3<float>& data_right_arm_pose)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_right_arm_pose"), data_right_arm_pose);
    }

    void ArmorStandEntity::SetDataLeftLegPose(const Vector3<float>& data_left_leg_pose)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_left_leg_pose"), data_left_leg_pose);
    }

    void ArmorStandEntity::SetDataRightLegPose(const Vector3<float>& data_right_leg_pose)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_right_leg_pose"), data_right_leg_pose);
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
