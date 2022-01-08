#include "botcraft/Game/Entities/entities/monster/CreeperEntity.hpp"

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
    }

    CreeperEntity::~CreeperEntity()
    {

    }


    std::string CreeperEntity::GetName() const
    {
        return "Creeper";
    }

    EntityType CreeperEntity::GetType() const
    {
        return EntityType::Creeper;
    }

    AABB CreeperEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double CreeperEntity::GetWidth() const
    {
        return 0.6;
    }

    double CreeperEntity::GetHeight() const
    {
        return 1.7;
    }


    std::string CreeperEntity::GetClassName()
    {
        return "Creeper";
    }

    EntityType CreeperEntity::GetClassType()
    {
        return EntityType::Creeper;
    }


    nlohmann::json CreeperEntity::Serialize() const
    {
        nlohmann::json output = MonsterEntity::Serialize();

        output["data_swell_dir"] = GetDataSwellDir();
        output["data_is_powered"] = GetDataIsPowered();
        output["data_is_ignited"] = GetDataIsIgnited();

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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int CreeperEntity::GetDataSwellDir() const
    {
        return std::any_cast<int>(metadata.at("data_swell_dir"));
    }

    bool CreeperEntity::GetDataIsPowered() const
    {
        return std::any_cast<bool>(metadata.at("data_is_powered"));
    }

    bool CreeperEntity::GetDataIsIgnited() const
    {
        return std::any_cast<bool>(metadata.at("data_is_ignited"));
    }


    void CreeperEntity::SetDataSwellDir(const int data_swell_dir)
    {
        metadata["data_swell_dir"] = data_swell_dir;
    }

    void CreeperEntity::SetDataIsPowered(const bool data_is_powered)
    {
        metadata["data_is_powered"] = data_is_powered;
    }

    void CreeperEntity::SetDataIsIgnited(const bool data_is_ignited)
    {
        metadata["data_is_ignited"] = data_is_ignited;
    }

}
