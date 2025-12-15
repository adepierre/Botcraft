#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class AbstractCowEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        AbstractCowEntity();
        virtual ~AbstractCowEntity();

        virtual bool IsAbstractCow() const override;

    };
}
#endif
