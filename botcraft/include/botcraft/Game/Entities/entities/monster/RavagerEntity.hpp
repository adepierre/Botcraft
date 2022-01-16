#if PROTOCOL_VERSION > 404
#pragma once

#include "botcraft/Game/Entities/entities/raid/RaiderEntity.hpp"

namespace Botcraft
{
    class RavagerEntity : public RaiderEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = RaiderEntity::metadata_count + RaiderEntity::hierarchy_metadata_count;

    public:
        RavagerEntity();
        virtual ~RavagerEntity();

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
