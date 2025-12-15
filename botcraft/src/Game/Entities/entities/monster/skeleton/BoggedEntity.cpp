#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/Entities/entities/monster/skeleton/BoggedEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, BoggedEntity::metadata_count> BoggedEntity::metadata_names{ {
        "data_sheared",
    } };

    BoggedEntity::BoggedEntity()
    {
        // Initialize all metadata with default values
        SetDataSheared(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 16.0) });
    }

    BoggedEntity::~BoggedEntity()
    {

    }


    std::string BoggedEntity::GetName() const
    {
        return "bogged";
    }

    EntityType BoggedEntity::GetType() const
    {
        return EntityType::Bogged;
    }


    std::string BoggedEntity::GetClassName()
    {
        return "bogged";
    }

    EntityType BoggedEntity::GetClassType()
    {
        return EntityType::Bogged;
    }


    ProtocolCraft::Json::Value BoggedEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractSkeletonEntity::Serialize();

        output["metadata"]["data_sheared"] = GetDataSheared();

        return output;
    }


    void BoggedEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractSkeletonEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool BoggedEntity::GetDataSheared() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_sheared"));
    }


    void BoggedEntity::SetDataSheared(const bool data_sheared)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_sheared"] = data_sheared;
    }


    double BoggedEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double BoggedEntity::GetHeightImpl() const
    {
        return 1.99;
    }

}
#endif
