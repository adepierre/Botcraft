#pragma once

#include "botcraft/Game/Entities/entities/PathfinderMobEntity.hpp"

namespace Botcraft
{
    class AgeableMobEntity : public PathfinderMobEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_baby_id"),
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
            std::string_view("age_locked"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = PathfinderMobEntity::metadata_count + PathfinderMobEntity::hierarchy_metadata_count;

    public:
        AgeableMobEntity();
        virtual ~AgeableMobEntity();

        virtual bool IsAgeableMob() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetDataBabyId() const;
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        bool GetAgeLocked() const;
#endif

        void SetDataBabyId(const bool data_baby_id);
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        void SetAgeLocked(const bool age_locked);
#endif

    };
}
