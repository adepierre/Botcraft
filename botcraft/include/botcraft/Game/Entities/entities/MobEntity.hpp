#pragma once

#include "botcraft/Game/Entities/entities/LivingEntity.hpp"

namespace Botcraft
{
    class MobEntity : public LivingEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_mob_flags_id"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = LivingEntity::metadata_count + LivingEntity::hierarchy_metadata_count;

    public:
        MobEntity();
        virtual ~MobEntity();

        virtual bool IsMob() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        char GetDataMobFlagsId() const;

        void SetDataMobFlagsId(const char data_mob_flags_id);

        // Attribute stuff
        double GetAttributeFollowRangeValue() const;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 767 /* < 1.21 */
        double GetAttributeAttackKnockbackValue() const;
#endif

    };
}
