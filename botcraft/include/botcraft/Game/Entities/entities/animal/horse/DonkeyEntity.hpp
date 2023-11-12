#pragma once

#include "botcraft/Game/Entities/entities/animal/horse/AbstractChestedHorseEntity.hpp"

namespace Botcraft
{
    class DonkeyEntity : public AbstractChestedHorseEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractChestedHorseEntity::metadata_count + AbstractChestedHorseEntity::hierarchy_metadata_count;

    public:
        DonkeyEntity();
        virtual ~DonkeyEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
