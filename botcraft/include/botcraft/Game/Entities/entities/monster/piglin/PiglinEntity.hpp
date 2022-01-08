#if PROTOCOL_VERSION > 578
#pragma once

#if PROTOCOL_VERSION > 736
#include "botcraft/Game/Entities/entities/monster/piglin/AbstractPiglinEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 736
    class PiglinEntity : public AbstractPiglinEntity
#else
    class PiglinEntity : public MonsterEntity
#endif
    {
    protected:
#if PROTOCOL_VERSION > 736
        static constexpr int metadata_count = 3;
#else
        static constexpr int metadata_count = 4;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
#if PROTOCOL_VERSION > 736
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
        virtual AABB GetCollider() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDataBabyId() const;
#if PROTOCOL_VERSION < 737
        bool GetDataImmuneToZombification() const;
#endif
        bool GetDataIsChargingCrossbow() const;
        bool GetDataIsDancing() const;

        void SetDataBabyId(const bool data_baby_id);
#if PROTOCOL_VERSION < 737
        void SetDataImmuneToZombification(const bool data_immune_to_zombification);
#endif
        void SetDataIsChargingCrossbow(const bool data_is_charging_crossbow);
        void SetDataIsDancing(const bool data_is_dancing);

    };
}
#endif
