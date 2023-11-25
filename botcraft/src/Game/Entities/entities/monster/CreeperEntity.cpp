#include "botcraft/Game/Entities/entities/monster/CreeperEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, CreeperEntity::metadata_count> CreeperEntity::metadata_names{ {
        "data_swell_dir",
        "data_is_powered",
        "data_is_ignited",
    } };

    CreeperEntity::CreeperEntity()
    {
        // Initialize all metadata with default values
        SetDataSwellDir(-1);
        SetDataIsPowered(false);
        SetDataIsIgnited(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
    }

    CreeperEntity::~CreeperEntity()
    {

    }


    std::string CreeperEntity::GetName() const
    {
        return "creeper";
    }

    EntityType CreeperEntity::GetType() const
    {
        return EntityType::Creeper;
    }


    std::string CreeperEntity::GetClassName()
    {
        return "creeper";
    }

    EntityType CreeperEntity::GetClassType()
    {
        return EntityType::Creeper;
    }


    ProtocolCraft::Json::Value CreeperEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_swell_dir"] = GetDataSwellDir();
        output["metadata"]["data_is_powered"] = GetDataIsPowered();
        output["metadata"]["data_is_ignited"] = GetDataIsIgnited();

        return output;
    }


    void CreeperEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int CreeperEntity::GetDataSwellDir() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_swell_dir"));
    }

    bool CreeperEntity::GetDataIsPowered() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_is_powered"));
    }

    bool CreeperEntity::GetDataIsIgnited() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_is_ignited"));
    }


    void CreeperEntity::SetDataSwellDir(const int data_swell_dir)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_swell_dir"] = data_swell_dir;
    }

    void CreeperEntity::SetDataIsPowered(const bool data_is_powered)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_is_powered"] = data_is_powered;
    }

    void CreeperEntity::SetDataIsIgnited(const bool data_is_ignited)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_is_ignited"] = data_is_ignited;
    }


    double CreeperEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double CreeperEntity::GetHeightImpl() const
    {
        return 1.7;
    }

}
