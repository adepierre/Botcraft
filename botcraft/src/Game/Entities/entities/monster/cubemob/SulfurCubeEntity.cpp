#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#include "botcraft/Game/Entities/entities/monster/cubemob/SulfurCubeEntity.hpp"
#include "botcraft/Utilities/Logger.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, SulfurCubeEntity::metadata_count> SulfurCubeEntity::metadata_names{ {
        "max_fuse",
        "from_bucket",
    } };

    SulfurCubeEntity::SulfurCubeEntity()
    {
        // Initialize all metadata with default values
        SetMaxFuse(-1);
        SetFromBucket(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::TemptRange, EntityAttribute(EntityAttribute::Type::TemptRange, 8.0) });
    }

    SulfurCubeEntity::~SulfurCubeEntity()
    {

    }


    std::string SulfurCubeEntity::GetName() const
    {
        return "sulfur_cube";
    }

    EntityType SulfurCubeEntity::GetType() const
    {
        return EntityType::SulfurCube;
    }


    std::string SulfurCubeEntity::GetClassName()
    {
        return "sulfur_cube";
    }

    EntityType SulfurCubeEntity::GetClassType()
    {
        return EntityType::SulfurCube;
    }


    ProtocolCraft::Json::Value SulfurCubeEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractCubeMobEntity::Serialize();

        output["metadata"]["max_fuse"] = GetMaxFuse();
        output["metadata"]["from_bucket"] = GetFromBucket();

        output["attributes"]["tempt_range"] = GetAttributeTemptRangeValue();

        return output;
    }


    void SulfurCubeEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractCubeMobEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int SulfurCubeEntity::GetMaxFuse() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("max_fuse"));
    }

    bool SulfurCubeEntity::GetFromBucket() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("from_bucket"));
    }


    void SulfurCubeEntity::SetMaxFuse(const int max_fuse)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["max_fuse"] = max_fuse;
    }

    void SulfurCubeEntity::SetFromBucket(const bool from_bucket)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["from_bucket"] = from_bucket;
    }


    double SulfurCubeEntity::GetAttributeTemptRangeValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::TemptRange).GetValue();
    }


    void SulfurCubeEntity::SizeChanged(const int new_size)
    {
        AbstractCubeMobEntity::SizeChanged(new_size);
        auto it = attributes.find(EntityAttribute::Type::MaxHealth);
        if (it != attributes.end())
        {
            it->second.SetBaseValue(static_cast<double>(new_size) * 4.0);
        }
        else
        {
            LOG_WARNING("Trying to set attribute base value for " << EntityAttribute::Type::MaxHealth << " for a sulfur cube but it doesn't have this attribute");
        }
    }

    double SulfurCubeEntity::GetWidthImpl() const
    {
        return 0.49;
    }

    double SulfurCubeEntity::GetHeightImpl() const
    {
        return 0.49;
    }

}
#endif
