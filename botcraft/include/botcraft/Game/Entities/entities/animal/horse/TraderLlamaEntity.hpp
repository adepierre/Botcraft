#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/horse/LlamaEntity.hpp"

namespace Botcraft
{
    class TraderLlamaEntity : public LlamaEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = LlamaEntity::metadata_count + LlamaEntity::hierarchy_metadata_count;

    public:
        TraderLlamaEntity();
        virtual ~TraderLlamaEntity();

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
