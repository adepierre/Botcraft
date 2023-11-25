#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#pragma once

#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
#include "botcraft/Game/Entities/entities/monster/piglin/AbstractPiglinEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
    class PiglinEntity : public AbstractPiglinEntity
#else
    class PiglinEntity : public MonsterEntity
#endif
    {
    protected:
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        static constexpr int metadata_count = 3;
#else
        static constexpr int metadata_count = 4;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        static constexpr int hierarchy_metadata_count = AbstractPiglinEntity::metadata_count + AbstractPiglinEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;
#endif

    public:
        PiglinEntity();
        virtual ~PiglinEntity();

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
#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
        bool GetDataImmuneToZombification() const;
#endif
        bool GetDataIsChargingCrossbow() const;
        bool GetDataIsDancing() const;

        void SetDataBabyId(const bool data_baby_id);
#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
        void SetDataImmuneToZombification(const bool data_immune_to_zombification);
#endif
        void SetDataIsChargingCrossbow(const bool data_is_charging_crossbow);
        void SetDataIsDancing(const bool data_is_dancing);

        // Attribute stuff

        // 766bfa64-11f3-11ea-8d71-362b9e155667
        static constexpr std::array<unsigned char, 16> speed_modifier_baby_uuid = { 0x76, 0x6B, 0xFA, 0x64, 0x11, 0xF3, 0x11, 0xEA, 0x8D, 0x71, 0x36, 0x2B, 0x9E, 0x15, 0x56, 0x67 };


    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
