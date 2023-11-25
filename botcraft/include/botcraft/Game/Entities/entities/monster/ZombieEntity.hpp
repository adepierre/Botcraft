#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class ZombieEntity : public MonsterEntity
    {
    protected:
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = 3;
#elif PROTOCOL_VERSION > 340 /* > 1.12.2 */
        static constexpr int metadata_count = 4;
#else
        static constexpr int metadata_count = 3;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        ZombieEntity();
        virtual ~ZombieEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDataBabyId() const;
        int GetDataSpecialTypeId() const;
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        bool GetDataAreHandsUp() const;
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        bool GetDataDrownedConversionId() const;
#endif

        void SetDataBabyId(const bool data_baby_id);
        void SetDataSpecialTypeId(const int data_special_type_id);
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        void SetDataAreHandsUp(const bool data_are_hands_up);
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        void SetDataDrownedConversionId(const bool data_drowned_conversion_id);
#endif

        // Attribute stuff
        double GetAttributeSpawnReinforcementsChanceValue() const;

        // b9766b59-9566-4402-bc1f-2ee2a276d836
        static constexpr std::array<unsigned char, 16> speed_modifier_baby_uuid = { 0xB9, 0x76, 0x6B, 0x59, 0x95, 0x66, 0x44, 0x2, 0xBC, 0x1F, 0x2E, 0xE2, 0xA2, 0x76, 0xD8, 0x36 };


    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
