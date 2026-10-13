#pragma once

#include "botcraft/Game/Entities/entities/TamableAnimalEntity.hpp"

namespace Botcraft
{
    class WolfEntity : public TamableAnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
#if PROTOCOL_VERSION < 499 /* < 1.15 */
            std::string_view("data_health_id"),
#endif
            std::string_view("data_interested_id"),
            std::string_view("data_collar_color"),
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
            std::string_view("data_remaining_anger_time"),
#else
            std::string_view("data_anger_end_time"),
#endif
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
            std::string_view("data_variant_id"),
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            std::string_view("data_sound_variant_id"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = TamableAnimalEntity::metadata_count + TamableAnimalEntity::hierarchy_metadata_count;

    public:
        WolfEntity();
        virtual ~WolfEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
#if PROTOCOL_VERSION < 499 /* < 1.15 */
        float GetDataHealthId() const;
#endif
        bool GetDataInterestedId() const;
        int GetDataCollarColor() const;
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
        int GetDataRemainingAngerTime() const;
#else
        long long int GetDataAngerEndTime() const;
#endif
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        int GetDataVariantId() const;
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        int GetDataSoundVariantId() const;
#endif

#if PROTOCOL_VERSION < 499 /* < 1.15 */
        void SetDataHealthId(const float data_health_id);
#endif
        void SetDataInterestedId(const bool data_interested_id);
        void SetDataCollarColor(const int data_collar_color);
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
        void SetDataRemainingAngerTime(const int data_remaining_anger_time);
#else
        void SetDataAngerEndTime(const long long int data_anger_end_time);
#endif
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        void SetDataVariantId(const int data_variant_id);
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        void SetDataSoundVariantId(const int data_sound_variant_id);
#endif

        // Attribute stuff
        double GetAttributeAttackDamageValue() const;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
