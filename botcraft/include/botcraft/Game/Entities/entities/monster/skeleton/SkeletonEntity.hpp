#pragma once

#include "botcraft/Game/Entities/entities/monster/skeleton/AbstractSkeletonEntity.hpp"

namespace Botcraft
{
    class SkeletonEntity : public AbstractSkeletonEntity
    {
    protected:
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        static constexpr int metadata_count = 1;
#else
        static constexpr int metadata_count = 0;
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        static const std::array<std::string, metadata_count> metadata_names;
#endif
        static constexpr int hierarchy_metadata_count = AbstractSkeletonEntity::metadata_count + AbstractSkeletonEntity::hierarchy_metadata_count;

    public:
        SkeletonEntity();
        virtual ~SkeletonEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDataStrayConversionId() const;

        void SetDataStrayConversionId(const bool data_stray_conversion_id);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
