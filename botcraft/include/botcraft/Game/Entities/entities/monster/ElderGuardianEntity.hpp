#pragma once

#include "botcraft/Game/Entities/entities/monster/GuardianEntity.hpp"

namespace Botcraft
{
    class ElderGuardianEntity : public GuardianEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = GuardianEntity::metadata_count + GuardianEntity::hierarchy_metadata_count;

    public:
        ElderGuardianEntity();
        virtual ~ElderGuardianEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual AABB GetCollider() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

    };
}