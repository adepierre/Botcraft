#pragma once

#if PROTOCOL_VERSION < 767 /* < 1.21 */
#include "botcraft/Game/Entities/entities/decoration/HangingEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/decoration/BlockAttachedEntity.hpp"
#endif

namespace Botcraft
{
    class LeashFenceKnotEntity :
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        public HangingEntity
#else
        public BlockAttachedEntity
#endif
    {
    protected:
        static constexpr int metadata_count = 0;
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        static constexpr int hierarchy_metadata_count = HangingEntity::metadata_count + HangingEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = BlockAttachedEntity::metadata_count + BlockAttachedEntity::hierarchy_metadata_count;
#endif

    public:
        LeashFenceKnotEntity();
        virtual ~LeashFenceKnotEntity();

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
