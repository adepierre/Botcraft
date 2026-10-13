#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class DisplayEntity : public Entity
    {
    private:
        static constexpr std::array metadata_names{
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            std::string_view("data_interpolation_start_delta_ticks_id"),
            std::string_view("data_interpolation_duration_id"),
#else
            std::string_view("data_transformation_interpolation_start_delta_ticks_id"),
            std::string_view("data_transformation_interpolation_duration_id"),
            std::string_view("data_pos_rot_interpolation_duration_id"),
#endif
            std::string_view("data_translation_id"),
            std::string_view("data_scale_id"),
            std::string_view("data_left_rotation_id"),
            std::string_view("data_right_rotation_id"),
            std::string_view("data_billboard_render_constraints_id"),
            std::string_view("data_brightness_override_id"),
            std::string_view("data_view_range_id"),
            std::string_view("data_shadow_radius_id"),
            std::string_view("data_shadow_strength_id"),
            std::string_view("data_width_id"),
            std::string_view("data_height_id"),
            std::string_view("data_glow_color_override_id"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        DisplayEntity();
        virtual ~DisplayEntity();

        virtual bool IsDisplay() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        int GetDataInterpolationStartDeltaTicksId() const;
        int GetDataInterpolationDurationId() const;
#else
        int GetDataTransformationInterpolationStartDeltaTicksId() const;
        int GetDataTransformationInterpolationDurationId() const;
        int GetDataPosRotInterpolationDurationId() const;
#endif
        Vector3<float> GetDataTranslationId() const;
        Vector3<float> GetDataScaleId() const;
        std::array<float, 4> GetDataLeftRotationId() const;
        std::array<float, 4> GetDataRightRotationId() const;
        char GetDataBillboardRenderConstraintsId() const;
        int GetDataBrightnessOverrideId() const;
        float GetDataViewRangeId() const;
        float GetDataShadowRadiusId() const;
        float GetDataShadowStrengthId() const;
        float GetDataWidthId() const;
        float GetDataHeightId() const;
        int GetDataGlowColorOverrideId() const;

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetDataInterpolationStartDeltaTicksId(const int data_interpolation_start_delta_ticks_id);
        void SetDataInterpolationDurationId(const int data_interpolation_duration_id);
#else
        void SetDataTransformationInterpolationStartDeltaTicksId(const int data_transformation_interpolation_start_delta_ticks_id);
        void SetDataTransformationInterpolationDurationId(const int data_transformation_interpolation_duration_id);
        void SetDataPosRotInterpolationDurationId(const int data_pos_rot_interpolation_duration_id);
#endif
        void SetDataTranslationId(const Vector3<float> data_translation_id);
        void SetDataScaleId(const Vector3<float> data_scale_id);
        void SetDataLeftRotationId(const std::array<float, 4> data_left_rotation_id);
        void SetDataRightRotationId(const std::array<float, 4> data_right_rotation_id);
        void SetDataBillboardRenderConstraintsId(const char data_billboard_render_constraints_id);
        void SetDataBrightnessOverrideId(const int data_brightness_override_id);
        void SetDataViewRangeId(const float data_view_range_id);
        void SetDataShadowRadiusId(const float data_shadow_radius_id);
        void SetDataShadowStrengthId(const float data_shadow_strength_id);
        void SetDataWidthId(const float data_width_id);
        void SetDataHeightId(const float data_height_id);
        void SetDataGlowColorOverrideId(const int data_glow_color_override_id);

    };
}
#endif
