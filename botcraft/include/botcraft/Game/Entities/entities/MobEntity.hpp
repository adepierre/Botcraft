#pragma once

#include "botcraft/Game/Entities/entities/LivingEntity.hpp"

namespace Botcraft
{
    class MobEntity : public LivingEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = LivingEntity::metadata_count + LivingEntity::hierarchy_metadata_count;

    public:
        MobEntity();
        virtual ~MobEntity();

        virtual bool IsMob() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        char GetDataMobFlagsId() const;

        void SetDataMobFlagsId(const char data_mob_flags_id);

        // Attribute stuff
        double GetAttributeFollowRangeValue() const;
        double GetAttributeAttackKnockbackValue() const;

    };
}
