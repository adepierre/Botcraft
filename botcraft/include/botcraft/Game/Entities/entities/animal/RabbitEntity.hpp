#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class RabbitEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        RabbitEntity();
        virtual ~RabbitEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataTypeId() const;

        void SetDataTypeId(const int data_type_id);

        // Attribute stuff
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        double GetAttributeAttackDamageValue() const;
#endif

#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        inline static const std::string killer_bunny_modifier_key = "minecraft:killer_bunny";
        inline static const std::string evil_attack_power_modifier_key = "minecraft:evil";
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
