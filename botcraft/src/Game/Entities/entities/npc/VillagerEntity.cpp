#include "botcraft/Game/Entities/entities/npc/VillagerEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, VillagerEntity::metadata_count> VillagerEntity::metadata_names{ {
#if PROTOCOL_VERSION > 404
        "data_villager_data",
#else
        "data_villager_profession_id",
#endif
    } };

    VillagerEntity::VillagerEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION > 404
        SetDataVillagerData(VillagerData{ 2, 0, 1 });
#else
        SetDataVillagerProfessionId(0);
#endif
    }

    VillagerEntity::~VillagerEntity()
    {

    }


    std::string VillagerEntity::GetName() const
    {
        return "Villager";
    }

    EntityType VillagerEntity::GetType() const
    {
        return EntityType::Villager;
    }

    AABB VillagerEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double VillagerEntity::GetWidth() const
    {
        return 0.6;
    }

    double VillagerEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string VillagerEntity::GetClassName()
    {
        return "Villager";
    }

    EntityType VillagerEntity::GetClassType()
    {
        return EntityType::Villager;
    }


    nlohmann::json VillagerEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 477
        nlohmann::json output = AbstractVillagerEntity::Serialize();
#else
        nlohmann::json output = AgeableMobEntity::Serialize();
#endif

#if PROTOCOL_VERSION > 404
        output["data_villager_data"] = { GetDataVillagerData().type, GetDataVillagerData().profession, GetDataVillagerData().level };
#else
        output["data_villager_profession_id"] = std::any_cast<int>(GetDataVillagerProfessionId());
#endif

        return output;
    }


    void VillagerEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION > 477
            AbstractVillagerEntity::SetMetadataValue(index, value);
#else
            AgeableMobEntity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

#if PROTOCOL_VERSION > 404
    const VillagerData& VillagerEntity::GetDataVillagerData() const
    {
        return std::any_cast<const VillagerData&>(metadata.at("data_villager_data"));
    }


    void VillagerEntity::SetDataVillagerData(const VillagerData& data_villager_data)
    {
        metadata["data_villager_data"] = data_villager_data;
    }
#else
    int VillagerEntity::GetDataVillagerProfessionId() const
    {
        return std::any_cast<int>(metadata.at("data_villager_profession_id"));
    }


    void VillagerEntity::SetDataVillagerProfessionId(const int data_villager_profession_id)
    {
        metadata["data_villager_profession_id"] = data_villager_profession_id;
    }
#endif
}
