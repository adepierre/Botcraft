#if PROTOCOL_VERSION > 758
#pragma once

#include "botcraft/Game/Entities/entities/PathfinderMobEntity.hpp"

namespace Botcraft
{
    class AllayEntity : public PathfinderMobEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = PathfinderMobEntity::metadata_count + PathfinderMobEntity::hierarchy_metadata_count;

    public:
        AllayEntity();
        virtual ~AllayEntity();

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
