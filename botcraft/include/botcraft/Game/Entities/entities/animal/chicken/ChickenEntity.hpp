#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class ChickenEntity : public AnimalEntity
    {
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_variant_id"),
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
            std::string_view("data_sound_variant_id"),
#endif
        };
#endif
    protected:
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
#endif
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        ChickenEntity();
        virtual ~ChickenEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataVariantId() const;
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        int GetDataSoundVariantId() const;
#endif

        void SetDataVariantId(const int data_variant_id);
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        void SetDataSoundVariantId(const int data_sound_variant_id);
#endif
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
