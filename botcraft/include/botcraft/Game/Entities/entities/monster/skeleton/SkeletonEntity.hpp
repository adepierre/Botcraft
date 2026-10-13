#pragma once

#include "botcraft/Game/Entities/entities/monster/skeleton/AbstractSkeletonEntity.hpp"

namespace Botcraft
{
    class SkeletonEntity : public AbstractSkeletonEntity
    {
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_stray_conversion_id"),
        };
#endif
    protected:
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
#else
        static constexpr int metadata_count = 0;
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
        bool GetDataStrayConversionId() const;

        void SetDataStrayConversionId(const bool data_stray_conversion_id);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
