#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class AbstractSkeletonEntity : public MonsterEntity
    {
    protected:
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#endif
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        AbstractSkeletonEntity();
        virtual ~AbstractSkeletonEntity();

        virtual bool IsAbstractSkeleton() const override;


#if PROTOCOL_VERSION < 405 /* < 1.14 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetIsSwingingArms() const;

        void SetIsSwingingArms(const bool is_swinging_arms);
#endif

    };
}
