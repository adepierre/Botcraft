#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/nautilus/AbstractNautilusEntity.hpp"

namespace Botcraft
{
    class NautilusEntity : public AbstractNautilusEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractNautilusEntity::metadata_count + AbstractNautilusEntity::hierarchy_metadata_count;

    public:
        NautilusEntity();
        virtual ~NautilusEntity();

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
