#pragma once

#include "botcraft/Game/Entities/entities/projectile/FireballEntity.hpp"

namespace Botcraft
{
    class SmallFireballEntity : public FireballEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = FireballEntity::metadata_count + FireballEntity::hierarchy_metadata_count;

    public:
        SmallFireballEntity();
        virtual ~SmallFireballEntity();

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
