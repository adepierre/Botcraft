#pragma once

#include "botcraft/Game/Entities/entities/animal/ShoulderRidingEntity.hpp"

namespace Botcraft
{
    class ParrotEntity : public ShoulderRidingEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = ShoulderRidingEntity::metadata_count + ShoulderRidingEntity::hierarchy_metadata_count;

    public:
        ParrotEntity();
        virtual ~ParrotEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataVariantId() const;

        void SetDataVariantId(const int data_variant_id);

        // Attribute stuff
        double GetAttributeFlyingSpeedValue() const;
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        double GetAttributeAttackDamageValue() const;
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
