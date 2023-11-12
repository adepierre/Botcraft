#include "botcraft/Game/Entities/entities/boss/enderdragon/EnderDragonEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, EnderDragonEntity::metadata_count> EnderDragonEntity::metadata_names{ {
        "data_phase",
    } };

    EnderDragonEntity::EnderDragonEntity()
    {
        // Initialize all metadata with default values
        SetDataPhase(10);
    }

    EnderDragonEntity::~EnderDragonEntity()
    {

    }


    std::string EnderDragonEntity::GetName() const
    {
        return "ender_dragon";
    }

    EntityType EnderDragonEntity::GetType() const
    {
        return EntityType::EnderDragon;
    }


    std::string EnderDragonEntity::GetClassName()
    {
        return "ender_dragon";
    }

    EntityType EnderDragonEntity::GetClassType()
    {
        return EntityType::EnderDragon;
    }


    ProtocolCraft::Json::Value EnderDragonEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MobEntity::Serialize();

        output["metadata"]["data_phase"] = GetDataPhase();

        return output;
    }


    void EnderDragonEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MobEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int EnderDragonEntity::GetDataPhase() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_phase"));
    }


    void EnderDragonEntity::SetDataPhase(const int data_phase)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_phase"] = data_phase;
    }


    double EnderDragonEntity::GetWidthImpl() const
    {
        return 16.0;
    }

    double EnderDragonEntity::GetHeightImpl() const
    {
        return 8.0;
    }

}
