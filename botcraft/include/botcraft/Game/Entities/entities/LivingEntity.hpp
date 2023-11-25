#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"
#include "botcraft/Game/Entities/EntityAttribute.hpp"

#include <array>

namespace Botcraft
{
    class LivingEntity : public Entity
    {
    protected:
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        static constexpr int metadata_count = 7;
#elif PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = 6;
#else
        static constexpr int metadata_count = 5;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        LivingEntity();
        virtual ~LivingEntity();

        virtual bool IsLivingEntity() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        char GetDataLivingEntityFlags() const;
        float GetDataHealthId() const;
        int GetDataEffectColorId() const;
        bool GetDataEffectAmbienceId() const;
        int GetDataArrowCountId() const;
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        int GetDataStingerCountId() const;
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        std::optional<Position> GetSleepingPosId() const;
#endif

        void SetDataLivingEntityFlags(const char data_living_entity_flags);
        void SetDataHealthId(const float data_health_id);
        void SetDataEffectColorId(const int data_effect_color_id);
        void SetDataEffectAmbienceId(const bool data_effect_ambience_id);
        void SetDataArrowCountId(const int data_arrow_count_id);
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        void SetDataStingerCountId(const int data_stinger_count_id);
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        void SetSleepingPosId(const std::optional<Position>& sleeping_pos_id);
#endif

        // Attribute stuff
        std::optional<EntityAttribute> GetAttribute(const EntityAttribute::Type type) const;

        void SetAttributeBaseValue(const EntityAttribute::Type type, const double value);
        void RemoveAttributeModifier(const EntityAttribute::Type type, const std::array<unsigned char, 16>& uuid);
        void SetAttributeModifier(const EntityAttribute::Type type, const std::array<unsigned char, 16>& uuid, const EntityAttribute::Modifier& modifier);
        void ClearModifiers(const EntityAttribute::Type type);
        void AddAttribute(const EntityAttribute& attribute);

        double GetAttributeMaxHealthValue() const;
        double GetAttributeKnockbackResistanceValue() const;
        double GetAttributeMovementSpeedValue() const;
        double GetAttributeArmorValue() const;
        double GetAttributeArmorToughnessValue() const;
        double GetAttributeMaxAbsorptionValue() const;

        // 87f46a96-686f-4796-b035-22e16ee9e038
        static constexpr std::array<unsigned char, 16> speed_modifier_soul_speed_uuid = { 0x87, 0xF4, 0x6A, 0x96, 0x68, 0x6F, 0x47, 0x96, 0xB0, 0x35, 0x22, 0xE1, 0x6E, 0xE9, 0xE0, 0x38 };
        // 1eaf83ff-7207-4596-b37a-d7a07b3ec4ce
        static constexpr std::array<unsigned char, 16> speed_modifier_powder_snow_uuid = { 0x1E, 0xAF, 0x83, 0xFF, 0x72, 0x7, 0x45, 0x96, 0xB3, 0x7A, 0xD7, 0xA0, 0x7B, 0x3E, 0xC4, 0xCE };
        // 662a6b8d-da3e-4c1c-8813-96ea6097278d
        static constexpr std::array<unsigned char, 16> speed_modifier_sprinting_uuid = { 0x66, 0x2A, 0x6B, 0x8D, 0xDA, 0x3E, 0x4C, 0x1C, 0x88, 0x13, 0x96, 0xEA, 0x60, 0x97, 0x27, 0x8D };


    protected:
        std::map<EntityAttribute::Type, EntityAttribute> attributes;

    };
}
