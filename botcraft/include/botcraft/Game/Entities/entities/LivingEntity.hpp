#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class LivingEntity : public Entity
    {
    protected:
#if PROTOCOL_VERSION > 498
        static constexpr int metadata_count = 7;
#elif PROTOCOL_VERSION > 404
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
#if PROTOCOL_VERSION > 498
        int GetDataStingerCountId() const;
#endif
#if PROTOCOL_VERSION > 404
        const std::optional<Position>& GetSleepingPosId() const;
#endif

        void SetDataLivingEntityFlags(const char data_living_entity_flags);
        void SetDataHealthId(const float data_health_id);
        void SetDataEffectColorId(const int data_effect_color_id);
        void SetDataEffectAmbienceId(const bool data_effect_ambience_id);
        void SetDataArrowCountId(const int data_arrow_count_id);
#if PROTOCOL_VERSION > 498
        void SetDataStingerCountId(const int data_stinger_count_id);
#endif
#if PROTOCOL_VERSION > 404
        void SetSleepingPosId(const std::optional<Position>& sleeping_pos_id);
#endif

    };
}
