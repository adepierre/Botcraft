#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/Entities/entities/OminousItemSpawnerEntity.hpp"

namespace Botcraft
{
    OminousItemSpawnerEntity::OminousItemSpawnerEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    ProtocolCraft::Slot OminousItemSpawnerEntity::GetDataItem() const
    {
        return GetMetadata<ProtocolCraft::Slot>(BOTCRAFT_ENTITY_METADATA_INDEX("data_item"));
    }


    void OminousItemSpawnerEntity::SetDataItem(const ProtocolCraft::Slot& data_item)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_item"), data_item);
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
