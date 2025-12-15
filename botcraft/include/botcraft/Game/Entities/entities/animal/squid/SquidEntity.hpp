#pragma once

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include "botcraft/Game/Entities/entities/animal/fish/WaterAnimalEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/animal/AgeableWaterCreatureEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    class SquidEntity : public WaterAnimalEntity
#else
    class SquidEntity : public AgeableWaterCreatureEntity
#endif
    {
    protected:
        static constexpr int metadata_count = 0;
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        static constexpr int hierarchy_metadata_count = WaterAnimalEntity::metadata_count + WaterAnimalEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = AgeableWaterCreatureEntity::metadata_count + AgeableWaterCreatureEntity::hierarchy_metadata_count;
#endif

    public:
        SquidEntity();
        virtual ~SquidEntity();

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
