#include "botcraft/Game/Entities/entities/monster/skeleton/SkeletonEntity.hpp"

namespace Botcraft
{
    SkeletonEntity::SkeletonEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        SetDataStrayConversionId(false);
#endif
    }

    SkeletonEntity::~SkeletonEntity()
    {

    }


    std::string SkeletonEntity::GetName() const
    {
        return "skeleton";
    }

    EntityType SkeletonEntity::GetType() const
    {
        return EntityType::Skeleton;
    }


    std::string SkeletonEntity::GetClassName()
    {
        return "skeleton";
    }

    EntityType SkeletonEntity::GetClassType()
    {
        return EntityType::Skeleton;
    }


#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    ProtocolCraft::Json::Value SkeletonEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractSkeletonEntity::Serialize();

        output["metadata"]["data_stray_conversion_id"] = GetDataStrayConversionId();

        return output;
    }


    bool SkeletonEntity::GetDataStrayConversionId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_stray_conversion_id"));
    }


    void SkeletonEntity::SetDataStrayConversionId(const bool data_stray_conversion_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_stray_conversion_id"), data_stray_conversion_id);
    }
#endif


    double SkeletonEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double SkeletonEntity::GetHeightImpl() const
    {
        return 1.99;
    }

}
