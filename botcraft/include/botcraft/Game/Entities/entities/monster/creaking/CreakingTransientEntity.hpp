#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "botcraft/Game/Entities/entities/monster/creaking/CreakingEntity.hpp"

namespace Botcraft
{
    class CreakingTransientEntity : public CreakingEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = CreakingEntity::metadata_count + CreakingEntity::hierarchy_metadata_count;

    public:
        CreakingTransientEntity();
        virtual ~CreakingTransientEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

    };
}
#endif
