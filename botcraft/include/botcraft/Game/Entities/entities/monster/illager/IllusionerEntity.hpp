#pragma once

#include "botcraft/Game/Entities/entities/monster/illager/SpellcasterIllagerEntity.hpp"

namespace Botcraft
{
    class IllusionerEntity : public SpellcasterIllagerEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = SpellcasterIllagerEntity::metadata_count + SpellcasterIllagerEntity::hierarchy_metadata_count;

    public:
        IllusionerEntity();
        virtual ~IllusionerEntity();

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
