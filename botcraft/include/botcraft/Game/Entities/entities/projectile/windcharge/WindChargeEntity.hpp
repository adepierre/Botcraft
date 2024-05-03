#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "botcraft/Game/Entities/entities/projectile/windcharge/AbstractWindChargeEntity.hpp"

namespace Botcraft
{
    class WindChargeEntity : public AbstractWindChargeEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractWindChargeEntity::metadata_count + AbstractWindChargeEntity::hierarchy_metadata_count;

    public:
        WindChargeEntity();
        virtual ~WindChargeEntity();

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
#endif
