#if PROTOCOL_VERSION > 773 /* > 1.21.11 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/camel/CamelEntity.hpp"

namespace Botcraft
{
    class CamelHuskEntity : public CamelEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = CamelEntity::metadata_count + CamelEntity::hierarchy_metadata_count;

    public:
        CamelHuskEntity();
        virtual ~CamelHuskEntity();

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
