#include "botcraft/Game/Entities/entities/monster/SkeletonEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION > 754
    const std::array<std::string, SkeletonEntity::metadata_count> SkeletonEntity::metadata_names{ {
        "data_stray_conversion_id",
    } };
#endif

    SkeletonEntity::SkeletonEntity()
    {
#if PROTOCOL_VERSION > 754
        // Initialize all metadata with default values
        SetDataStrayConversionId(false);
#endif
    }

    SkeletonEntity::~SkeletonEntity()
    {

    }


    std::string SkeletonEntity::GetName() const
    {
        return "Skeleton";
    }

    EntityType SkeletonEntity::GetType() const
    {
        return EntityType::Skeleton;
    }

    double SkeletonEntity::GetWidth() const
    {
        return 0.6;
    }

    double SkeletonEntity::GetHeight() const
    {
        return 1.99;
    }


    std::string SkeletonEntity::GetClassName()
    {
        return "Skeleton";
    }

    EntityType SkeletonEntity::GetClassType()
    {
        return EntityType::Skeleton;
    }


#if PROTOCOL_VERSION > 754
    ProtocolCraft::Json::Value SkeletonEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractSkeletonEntity::Serialize();

        output["metadata"]["data_stray_conversion_id"] = GetDataStrayConversionId();

        return output;
    }


    void SkeletonEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractSkeletonEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool SkeletonEntity::GetDataStrayConversionId() const
    {
        return std::any_cast<bool>(metadata.at("data_stray_conversion_id"));
    }


    void SkeletonEntity::SetDataStrayConversionId(const bool data_stray_conversion_id)
    {
        metadata["data_stray_conversion_id"] = data_stray_conversion_id;
    }
#endif

}
