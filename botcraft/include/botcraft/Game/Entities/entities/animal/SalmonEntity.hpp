#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AbstractSchoolingFishEntity.hpp"

namespace Botcraft
{
    class SalmonEntity : public AbstractSchoolingFishEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractSchoolingFishEntity::metadata_count + AbstractSchoolingFishEntity::hierarchy_metadata_count;

    public:
        SalmonEntity();
        virtual ~SalmonEntity();

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
