#if PROTOCOL_VERSION > 758
#pragma once

#include "botcraft/Game/Entities/entities/animal/AbstractFishEntity.hpp"

namespace Botcraft
{
    class TadpoleEntity : public AbstractFishEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractFishEntity::metadata_count + AbstractFishEntity::hierarchy_metadata_count;

    public:
        TadpoleEntity();
        virtual ~TadpoleEntity();

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
