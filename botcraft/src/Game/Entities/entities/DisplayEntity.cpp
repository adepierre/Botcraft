#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "botcraft/Game/Entities/entities/DisplayEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, DisplayEntity::metadata_count> DisplayEntity::metadata_names{ {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        "data_interpolation_start_delta_ticks_id",
        "data_interpolation_duration_id",
#else
        "data_transformation_interpolation_start_delta_ticks_id",
        "data_transformation_interpolation_duration_id",
        "data_pos_rot_interpolation_duration_id",
#endif
        "data_translation_id",
        "data_scale_id",
        "data_left_rotation_id",
        "data_right_rotation_id",
        "data_billboard_render_constraints_id",
        "data_brightness_override_id",
        "data_view_range_id",
        "data_shadow_radius_id",
        "data_shadow_strength_id",
        "data_width_id",
        "data_height_id",
        "data_glow_color_override_id",
    } };

    DisplayEntity::DisplayEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        SetDataInterpolationStartDeltaTicksId(0);
        SetDataInterpolationDurationId(0);
#else
        SetDataTransformationInterpolationStartDeltaTicksId(0);
        SetDataTransformationInterpolationDurationId(0);
        SetDataPosRotInterpolationDurationId(0);
#endif
        SetDataTranslationId({0.0f, 0.0f, 0.0f});
        SetDataScaleId({1.0f, 1.0f, 1.0f});
        SetDataLeftRotationId({0.0f, 0.0f, 0.0f, 0.0f});
        SetDataRightRotationId({0.0f, 0.0f, 0.0f, 0.0f});
        SetDataBillboardRenderConstraintsId(0);
        SetDataBrightnessOverrideId(-1);
        SetDataViewRangeId(1.0f);
        SetDataShadowRadiusId(0.0f);
        SetDataShadowStrengthId(1.0f);
        SetDataWidthId(0.0f);
        SetDataHeightId(0.0f);
        SetDataGlowColorOverrideId(-1);
    }

    DisplayEntity::~DisplayEntity()
    {

    }


    bool DisplayEntity::IsDisplay() const
    {
        return true;
    }


    ProtocolCraft::Json::Value DisplayEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        output["metadata"]["data_interpolation_start_delta_ticks_id"] = GetDataInterpolationStartDeltaTicksId();
        output["metadata"]["data_interpolation_duration_id"] = GetDataInterpolationDurationId();
#else
        output["metadata"]["data_transformation_interpolation_start_delta_ticks_id"] = GetDataTransformationInterpolationStartDeltaTicksId();
        output["metadata"]["data_transformation_interpolation_duration_id"] = GetDataTransformationInterpolationDurationId();
        output["metadata"]["data_pos_rot_interpolation_duration_id"] = GetDataPosRotInterpolationDurationId();
#endif
        output["metadata"]["data_translation_id"] = GetDataTranslationId().Serialize();
        output["metadata"]["data_scale_id"] = GetDataScaleId().Serialize();
        output["metadata"]["data_left_rotation_id"] = GetDataLeftRotationId();
        output["metadata"]["data_right_rotation_id"] = GetDataRightRotationId();
        output["metadata"]["data_billboard_render_constraints_id"] = GetDataBillboardRenderConstraintsId();
        output["metadata"]["data_brightness_override_id"] = GetDataBrightnessOverrideId();
        output["metadata"]["data_view_range_id"] = GetDataViewRangeId();
        output["metadata"]["data_shadow_radius_id"] = GetDataShadowRadiusId();
        output["metadata"]["data_shadow_strength_id"] = GetDataShadowStrengthId();
        output["metadata"]["data_width_id"] = GetDataWidthId();
        output["metadata"]["data_height_id"] = GetDataHeightId();
        output["metadata"]["data_glow_color_override_id"] = GetDataGlowColorOverrideId();

        return output;
    }


    void DisplayEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }


#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
    int DisplayEntity::GetDataInterpolationStartDeltaTicksId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_interpolation_start_delta_ticks_id"));
    }
    
    int DisplayEntity::GetDataInterpolationDurationId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_interpolation_duration_id"));
    }
#else
    int DisplayEntity::GetDataTransformationInterpolationStartDeltaTicksId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_transformation_interpolation_start_delta_ticks_id"));
    }

    int DisplayEntity::GetDataTransformationInterpolationDurationId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_transformation_interpolation_duration_id"));
    }

    int DisplayEntity::GetDataPosRotInterpolationDurationId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_pos_rot_interpolation_duration_id"));
    }
#endif
    
    Vector3<float> DisplayEntity::GetDataTranslationId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<Vector3<float>>(metadata.at("data_translation_id"));
    }
    
    Vector3<float> DisplayEntity::GetDataScaleId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<Vector3<float>>(metadata.at("data_scale_id"));
    }
    
    std::array<float, 4> DisplayEntity::GetDataLeftRotationId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<std::array<float, 4>>(metadata.at("data_left_rotation_id"));
    }
    
    std::array<float, 4> DisplayEntity::GetDataRightRotationId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<std::array<float, 4>>(metadata.at("data_right_rotation_id"));
    }
    
    char DisplayEntity::GetDataBillboardRenderConstraintsId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_billboard_render_constraints_id"));
    }
    
    int DisplayEntity::GetDataBrightnessOverrideId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_brightness_override_id"));
    }
    
    float DisplayEntity::GetDataViewRangeId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_view_range_id"));
    }
    
    float DisplayEntity::GetDataShadowRadiusId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_shadow_radius_id"));
    }
    
    float DisplayEntity::GetDataShadowStrengthId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_shadow_strength_id"));
    }
    
    float DisplayEntity::GetDataWidthId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_width_id"));
    }
    
    float DisplayEntity::GetDataHeightId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_height_id"));
    }
    
    int DisplayEntity::GetDataGlowColorOverrideId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_glow_color_override_id"));
    }
    

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
    void DisplayEntity::SetDataInterpolationStartDeltaTicksId(const int data_interpolation_start_delta_ticks_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_interpolation_start_delta_ticks_id"] = data_interpolation_start_delta_ticks_id;
    }
    
    void DisplayEntity::SetDataInterpolationDurationId(const int data_interpolation_duration_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_interpolation_duration_id"] = data_interpolation_duration_id;
    }
#else
    void DisplayEntity::SetDataTransformationInterpolationStartDeltaTicksId(const int data_transformation_interpolation_start_delta_ticks_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_transformation_interpolation_start_delta_ticks_id"] = data_transformation_interpolation_start_delta_ticks_id;
    }

    void DisplayEntity::SetDataTransformationInterpolationDurationId(const int data_transformation_interpolation_duration_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_transformation_interpolation_duration_id"] = data_transformation_interpolation_duration_id;
    }

    void DisplayEntity::SetDataPosRotInterpolationDurationId(const int data_pos_rot_interpolation_duration_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_pos_rot_interpolation_duration_id"] = data_pos_rot_interpolation_duration_id;
    }
#endif
    
    void DisplayEntity::SetDataTranslationId(const Vector3<float> data_translation_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_translation_id"] = data_translation_id;
    }
    
    void DisplayEntity::SetDataScaleId(const Vector3<float> data_scale_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_scale_id"] = data_scale_id;
    }
    
    void DisplayEntity::SetDataLeftRotationId(const std::array<float, 4> data_left_rotation_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_left_rotation_id"] = data_left_rotation_id;
    }
    
    void DisplayEntity::SetDataRightRotationId(const std::array<float, 4> data_right_rotation_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_right_rotation_id"] = data_right_rotation_id;
    }
    
    void DisplayEntity::SetDataBillboardRenderConstraintsId(const char data_billboard_render_constraints_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_billboard_render_constraints_id"] = data_billboard_render_constraints_id;
    }
    
    void DisplayEntity::SetDataBrightnessOverrideId(const int data_brightness_override_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_brightness_override_id"] = data_brightness_override_id;
    }
    
    void DisplayEntity::SetDataViewRangeId(const float data_view_range_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_view_range_id"] = data_view_range_id;
    }
    
    void DisplayEntity::SetDataShadowRadiusId(const float data_shadow_radius_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_shadow_radius_id"] = data_shadow_radius_id;
    }
    
    void DisplayEntity::SetDataShadowStrengthId(const float data_shadow_strength_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_shadow_strength_id"] = data_shadow_strength_id;
    }
    
    void DisplayEntity::SetDataWidthId(const float data_width_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_width_id"] = data_width_id;
    }
    
    void DisplayEntity::SetDataHeightId(const float data_height_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_height_id"] = data_height_id;
    }
    
    void DisplayEntity::SetDataGlowColorOverrideId(const int data_glow_color_override_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_glow_color_override_id"] = data_glow_color_override_id;
    }
}
#endif
