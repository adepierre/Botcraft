#pragma once

#if PROTOCOL_VERSION < 776 /* < 26.2 */
#include "botcraft/Game/Entities/entities/monster/cubemob/SlimeEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/monster/cubemob/AbstractCubeMobEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 776 /* < 26.2 */
    class MagmaCubeEntity : public SlimeEntity
#else
    class MagmaCubeEntity : public AbstractCubeMobEntity
#endif
    {
    protected:
        static constexpr int metadata_count = 0;
#if PROTOCOL_VERSION < 776 /* < 26.2 */
        static constexpr int hierarchy_metadata_count = SlimeEntity::metadata_count + SlimeEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = AbstractCubeMobEntity::metadata_count + AbstractCubeMobEntity::hierarchy_metadata_count;
#endif

    public:
        MagmaCubeEntity();
        virtual ~MagmaCubeEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
    protected:
        virtual void SizeChanged(const int new_size) override;
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;
#endif

    };
}
