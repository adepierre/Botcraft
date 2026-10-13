#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#include "botcraft/Game/Entities/entities/monster/cubemob/SulfurCubeEntity.hpp"
#include "botcraft/Utilities/Logger.hpp"

namespace Botcraft
{
    SulfurCubeEntity::SulfurCubeEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    int SulfurCubeEntity::GetMaxFuse() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("max_fuse"));
    }

    bool SulfurCubeEntity::GetFromBucket() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("from_bucket"));
    }


    void SulfurCubeEntity::SetMaxFuse(const int max_fuse)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("max_fuse"), max_fuse);
    }

    void SulfurCubeEntity::SetFromBucket(const bool from_bucket)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("from_bucket"), from_bucket);
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
