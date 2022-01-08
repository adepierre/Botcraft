#include "botcraft/Game/Entities/entities/monster/AbstractSkeletonEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION < 405
    const std::array<std::string, AbstractSkeletonEntity::metadata_count> AbstractSkeletonEntity::metadata_names{ {
        "is_swinging_arms",
    } };
#endif

    AbstractSkeletonEntity::AbstractSkeletonEntity()
    {
#if PROTOCOL_VERSION < 405
        // Initialize all metadata with default values
        SetIsSwingingArms(false);
#endif
    }

    AbstractSkeletonEntity::~AbstractSkeletonEntity()
    {

    }

    bool AbstractSkeletonEntity::IsAbstractSkeleton() const
    {
        return true;
    }


#if PROTOCOL_VERSION < 405
    nlohmann::json AbstractSkeletonEntity::Serialize() const
    {
        nlohmann::json output = MonsterEntity::Serialize();

        output["is_swinging_arms"] = GetIsSwingingArms();

        return output;
    }


    void AbstractSkeletonEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool AbstractSkeletonEntity::GetIsSwingingArms() const
    {
        return std::any_cast<bool>(metadata.at("is_swinging_arms"));
    }


    void AbstractSkeletonEntity::SetIsSwingingArms(const bool is_swinging_arms)
    {
        metadata["is_swinging_arms"] = is_swinging_arms;
    }
#endif

}
