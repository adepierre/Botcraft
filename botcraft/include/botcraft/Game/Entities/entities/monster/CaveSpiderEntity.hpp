#pragma once

#include "botcraft/Game/Entities/entities/monster/SpiderEntity.hpp"

namespace Botcraft
{
    class CaveSpiderEntity : public SpiderEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = SpiderEntity::metadata_count + SpiderEntity::hierarchy_metadata_count;

    public:
        CaveSpiderEntity();
        virtual ~CaveSpiderEntity();

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
