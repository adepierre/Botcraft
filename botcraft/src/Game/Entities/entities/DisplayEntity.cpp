#if PROTOCOL_VERSION > 761
#include "botcraft/Game/Entities/entities/DisplayEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, DisplayEntity::metadata_count> DisplayEntity::metadata_names{ {
        "data_interpolation_start_delta_ticks_id",
        "data_interpolation_duration_id",
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
        SetDataInterpolationStartDeltaTicksId(0);
        SetDataInterpolationDurationId(0);
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
        
        output["metadata"]["data_interpolation_start_delta_ticks_id"] = GetDataInterpolationStartDeltaTicksId();
        output["metadata"]["data_interpolation_duration_id"] = GetDataInterpolationDurationId();
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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    
    int DisplayEntity::GetDataInterpolationStartDeltaTicksId() const
    {
        return std::any_cast<int>(metadata.at("data_interpolation_start_delta_ticks_id"));
    }
    
    int DisplayEntity::GetDataInterpolationDurationId() const
    {
        return std::any_cast<int>(metadata.at("data_interpolation_duration_id"));
    }
    
    Vector3<float> DisplayEntity::GetDataTranslationId() const
    {
        return std::any_cast<Vector3<float>>(metadata.at("data_translation_id"));
    }
    
    Vector3<float> DisplayEntity::GetDataScaleId() const
    {
        return std::any_cast<Vector3<float>>(metadata.at("data_scale_id"));
    }
    
    std::array<float, 4> DisplayEntity::GetDataLeftRotationId() const
    {
        return std::any_cast<std::array<float, 4>>(metadata.at("data_left_rotation_id"));
    }
    
    std::array<float, 4> DisplayEntity::GetDataRightRotationId() const
    {
        return std::any_cast<std::array<float, 4>>(metadata.at("data_right_rotation_id"));
    }
    
    char DisplayEntity::GetDataBillboardRenderConstraintsId() const
    {
        return std::any_cast<char>(metadata.at("data_billboard_render_constraints_id"));
    }
    
    int DisplayEntity::GetDataBrightnessOverrideId() const
    {
        return std::any_cast<int>(metadata.at("data_brightness_override_id"));
    }
    
    float DisplayEntity::GetDataViewRangeId() const
    {
        return std::any_cast<float>(metadata.at("data_view_range_id"));
    }
    
    float DisplayEntity::GetDataShadowRadiusId() const
    {
        return std::any_cast<float>(metadata.at("data_shadow_radius_id"));
    }
    
    float DisplayEntity::GetDataShadowStrengthId() const
    {
        return std::any_cast<float>(metadata.at("data_shadow_strength_id"));
    }
    
    float DisplayEntity::GetDataWidthId() const
    {
        return std::any_cast<float>(metadata.at("data_width_id"));
    }
    
    float DisplayEntity::GetDataHeightId() const
    {
        return std::any_cast<float>(metadata.at("data_height_id"));
    }
    
    int DisplayEntity::GetDataGlowColorOverrideId() const
    {
        return std::any_cast<int>(metadata.at("data_glow_color_override_id"));
    }
    
    
    void DisplayEntity::SetDataInterpolationStartDeltaTicksId(const int data_interpolation_start_delta_ticks_id)
    {
        metadata["data_interpolation_start_delta_ticks_id"] = data_interpolation_start_delta_ticks_id;
    }
    
    void DisplayEntity::SetDataInterpolationDurationId(const int data_interpolation_duration_id)
    {
        metadata["data_interpolation_duration_id"] = data_interpolation_duration_id;
    }
    
    void DisplayEntity::SetDataTranslationId(const Vector3<float> data_translation_id)
    {
        metadata["data_translation_id"] = data_translation_id;
    }
    
    void DisplayEntity::SetDataScaleId(const Vector3<float> data_scale_id)
    {
        metadata["data_scale_id"] = data_scale_id;
    }
    
    void DisplayEntity::SetDataLeftRotationId(const std::array<float, 4> data_left_rotation_id)
    {
        metadata["data_left_rotation_id"] = data_left_rotation_id;
    }
    
    void DisplayEntity::SetDataRightRotationId(const std::array<float, 4> data_right_rotation_id)
    {
        metadata["data_right_rotation_id"] = data_right_rotation_id;
    }
    
    void DisplayEntity::SetDataBillboardRenderConstraintsId(const char data_billboard_render_constraints_id)
    {
        metadata["data_billboard_render_constraints_id"] = data_billboard_render_constraints_id;
    }
    
    void DisplayEntity::SetDataBrightnessOverrideId(const int data_brightness_override_id)
    {
        metadata["data_brightness_override_id"] = data_brightness_override_id;
    }
    
    void DisplayEntity::SetDataViewRangeId(const float data_view_range_id)
    {
        metadata["data_view_range_id"] = data_view_range_id;
    }
    
    void DisplayEntity::SetDataShadowRadiusId(const float data_shadow_radius_id)
    {
        metadata["data_shadow_radius_id"] = data_shadow_radius_id;
    }
    
    void DisplayEntity::SetDataShadowStrengthId(const float data_shadow_strength_id)
    {
        metadata["data_shadow_strength_id"] = data_shadow_strength_id;
    }
    
    void DisplayEntity::SetDataWidthId(const float data_width_id)
    {
        metadata["data_width_id"] = data_width_id;
    }
    
    void DisplayEntity::SetDataHeightId(const float data_height_id)
    {
        metadata["data_height_id"] = data_height_id;
    }
    
    void DisplayEntity::SetDataGlowColorOverrideId(const int data_glow_color_override_id)
    {
        metadata["data_glow_color_override_id"] = data_glow_color_override_id;
    }
}
#endif
