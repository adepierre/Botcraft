#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once

#include "botcraft/Game/Entities/entities/TamableAnimalEntity.hpp"

namespace Botcraft
{
    class WolfEntity : public TamableAnimalEntity
    {
    protected:

        static constexpr int metadata_count = 5;
        static const std::array<std::string, metadata_count> metadata_names;
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
        virtual void SetMetadataValue(const int index, const std::any& value) override;


        bool GetDataInterestedId() const;
        int GetDataCollarColor() const;
        int GetDataRemainingAngerTime() const;
        int GetDataVariantId() const;
        int GetDataSoundVariantId() const;

        void SetDataInterestedId(const bool data_interested_id);
        void SetDataCollarColor(const int data_collar_color);
        void SetDataRemainingAngerTime(const int data_remaining_anger_time);
        void SetDataVariantId(const int data_variant_id);
        void SetDataSoundVariantId(const int data_sound_variant_id);

        // Attribute stuff
        double GetAttributeAttackDamageValue() const;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
