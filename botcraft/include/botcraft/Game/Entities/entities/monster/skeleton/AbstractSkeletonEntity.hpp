#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class AbstractSkeletonEntity : public MonsterEntity
    {
#if PROTOCOL_VERSION < 405 /* < 1.14 */
    private:
        static constexpr std::array metadata_names{
            std::string_view("is_swinging_arms"),
        };
#endif
    protected:
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
#endif
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        AbstractSkeletonEntity();
        virtual ~AbstractSkeletonEntity();

        virtual bool IsAbstractSkeleton() const override;


#if PROTOCOL_VERSION < 405 /* < 1.14 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetIsSwingingArms() const;

        void SetIsSwingingArms(const bool is_swinging_arms);
#endif

    };
}
