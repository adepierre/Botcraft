#include "botcraft/Game/Entities/entities/npc/VillagerEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, VillagerEntity::metadata_count> VillagerEntity::metadata_names{ {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        "data_villager_data",
#else
        "data_villager_profession_id",
#endif
    } };

    VillagerEntity::VillagerEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
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
        return "villager";
    }

    EntityType VillagerEntity::GetType() const
    {
        return EntityType::Villager;
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
        return "villager";
    }

    EntityType VillagerEntity::GetClassType()
    {
        return EntityType::Villager;
    }


    ProtocolCraft::Json::Value VillagerEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 477 /* > 1.14 */
        ProtocolCraft::Json::Value output = AbstractVillagerEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = AgeableMobEntity::Serialize();
#endif

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        output["metadata"]["data_villager_data"] = { GetDataVillagerData().type, GetDataVillagerData().profession, GetDataVillagerData().level };
#else
        output["metadata"]["data_villager_profession_id"] = std::any_cast<int>(GetDataVillagerProfessionId());
#endif

        return output;
    }


    void VillagerEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION > 477 /* > 1.14 */
            AbstractVillagerEntity::SetMetadataValue(index, value);
#else
            AgeableMobEntity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    VillagerData VillagerEntity::GetDataVillagerData() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<VillagerData>(metadata.at("data_villager_data"));
    }


    void VillagerEntity::SetDataVillagerData(const VillagerData& data_villager_data)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_villager_data"] = data_villager_data;
    }
#else
    int VillagerEntity::GetDataVillagerProfessionId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_villager_profession_id"));
    }


    void VillagerEntity::SetDataVillagerProfessionId(const int data_villager_profession_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_villager_profession_id"] = data_villager_profession_id;
    }
#endif
}
