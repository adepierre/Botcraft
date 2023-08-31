#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#pragma once

#if PROTOCOL_VERSION > 477 /* > 1.14 */
#include "botcraft/Game/Entities/entities/npc/AbstractVillagerEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/AgeableMobEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 477 /* > 1.14 */
    class WanderingTraderEntity : public AbstractVillagerEntity
#else
    class WanderingTraderEntity : public AgeableMobEntity
#endif
    {
    protected:
        static constexpr int metadata_count = 0;
#if PROTOCOL_VERSION > 477 /* > 1.14 */
        static constexpr int hierarchy_metadata_count = AbstractVillagerEntity::metadata_count + AbstractVillagerEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = AgeableMobEntity::metadata_count + AgeableMobEntity::hierarchy_metadata_count;
#endif

    public:
        WanderingTraderEntity();
        virtual ~WanderingTraderEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

    };
}
#endif
