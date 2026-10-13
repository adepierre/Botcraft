#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class PigEntity : public AnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            std::string_view("data_saddle_id"),
#endif
            std::string_view("data_boost_time"),
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
            std::string_view("data_variant_id"),
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
            std::string_view("data_sound_variant_id"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        PigEntity();
        virtual ~PigEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        bool GetDataSaddleId() const;
#endif
        int GetDataBoostTime() const;
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        int GetDataVariantId() const;
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        int GetDataSoundVariantId() const;
#endif

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        void SetDataSaddleId(const bool data_saddle_id);
#endif
        void SetDataBoostTime(const int data_boost_time);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        void SetDataVariantId(const int data_variant_id);
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        void SetDataSoundVariantId(const int data_sound_variant_id);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
