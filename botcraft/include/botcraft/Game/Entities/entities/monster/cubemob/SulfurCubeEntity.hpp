#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#pragma once

#include "botcraft/Game/Entities/entities/monster/cubemob/AbstractCubeMobEntity.hpp"

namespace Botcraft
{
    class SulfurCubeEntity : public AbstractCubeMobEntity
    {
    protected:
        static constexpr int metadata_count = 2;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractCubeMobEntity::metadata_count + AbstractCubeMobEntity::hierarchy_metadata_count;

    public:
        SulfurCubeEntity();
        virtual ~SulfurCubeEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetMaxFuse() const;
        bool GetFromBucket() const;

        void SetMaxFuse(const int max_fuse);
        void SetFromBucket(const bool from_bucket);

        // Attribute stuff
        double GetAttributeTemptRangeValue() const;

    protected:
        virtual void SizeChanged(const int new_size) override;
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
