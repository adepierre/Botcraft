#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/Entities/entities/OminousItemSpawnerEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, OminousItemSpawnerEntity::metadata_count> OminousItemSpawnerEntity::metadata_names{ {
        "data_item",
    } };

    OminousItemSpawnerEntity::OminousItemSpawnerEntity()
    {
        // Initialize all metadata with default values
        SetDataItem(ProtocolCraft::Slot());
    }

    OminousItemSpawnerEntity::~OminousItemSpawnerEntity()
    {

    }


    std::string OminousItemSpawnerEntity::GetName() const
    {
        return "ominous_item_spawner";
    }

    EntityType OminousItemSpawnerEntity::GetType() const
    {
        return EntityType::OminousItemSpawner;
    }


    std::string OminousItemSpawnerEntity::GetClassName()
    {
        return "ominous_item_spawner";
    }

    EntityType OminousItemSpawnerEntity::GetClassType()
    {
        return EntityType::OminousItemSpawner;
    }


    ProtocolCraft::Json::Value OminousItemSpawnerEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_item"] = GetDataItem();

        return output;
    }


    void OminousItemSpawnerEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    ProtocolCraft::Slot OminousItemSpawnerEntity::GetDataItem() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const ProtocolCraft::Slot&>(metadata.at("data_item"));
    }


    void OminousItemSpawnerEntity::SetDataItem(const ProtocolCraft::Slot& data_item)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_item"] = data_item;
    }


    double OminousItemSpawnerEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double OminousItemSpawnerEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
#endif
