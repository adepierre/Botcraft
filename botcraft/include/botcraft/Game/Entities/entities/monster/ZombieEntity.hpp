#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class ZombieEntity : public MonsterEntity
    {
    protected:
#if PROTOCOL_VERSION > 404
        static constexpr int metadata_count = 3;
#elif PROTOCOL_VERSION > 340
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
        int GetDataSpecialTypeId() const;
#if PROTOCOL_VERSION < 405
        bool GetDataAreHandsUp() const;
#endif
#if PROTOCOL_VERSION > 340
        bool GetDataDrownedConversionId() const;
#endif

        void SetDataBabyId(const bool data_baby_id);
        void SetDataSpecialTypeId(const int data_special_type_id);
#if PROTOCOL_VERSION < 405
        void SetDataAreHandsUp(const bool data_are_hands_up);
#endif
#if PROTOCOL_VERSION > 340
        void SetDataDrownedConversionId(const bool data_drowned_conversion_id);
#endif

    };
}
