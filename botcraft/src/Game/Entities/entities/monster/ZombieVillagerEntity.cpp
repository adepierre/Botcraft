#include "botcraft/Game/Entities/entities/monster/ZombieVillagerEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, ZombieVillagerEntity::metadata_count> ZombieVillagerEntity::metadata_names{ {
        "data_converting_id",
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        "data_villager_data",
#else
        "data_villager_profession_id"
#endif
    } };

    ZombieVillagerEntity::ZombieVillagerEntity()
    {
        // Initialize all metadata with default values
        SetDataConvertingId(false);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        SetDataVillagerData(VillagerData{ 2, 0, 1 });
#else
        SetDataVillagerProfessionId(0);
#endif
    }

    ZombieVillagerEntity::~ZombieVillagerEntity()
    {

    }


    std::string ZombieVillagerEntity::GetName() const
    {
        return "zombie_villager";
    }

    EntityType ZombieVillagerEntity::GetType() const
    {
        return EntityType::ZombieVillager;
    }


    std::string ZombieVillagerEntity::GetClassName()
    {
        return "zombie_villager";
    }

    EntityType ZombieVillagerEntity::GetClassType()
    {
        return EntityType::ZombieVillager;
    }


    ProtocolCraft::Json::Value ZombieVillagerEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = ZombieEntity::Serialize();

        output["metadata"]["data_converting_id"] = GetDataConvertingId();
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        output["metadata"]["data_villager_data"] = { GetDataVillagerData().type, GetDataVillagerData().profession, GetDataVillagerData().level };
#else
        output["metadata"]["data_villager_profession_id"] = GetDataVillagerProfessionId();
#endif

        return output;
    }


    void ZombieVillagerEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            ZombieEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool ZombieVillagerEntity::GetDataConvertingId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_converting_id"));
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    VillagerData ZombieVillagerEntity::GetDataVillagerData() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<VillagerData>(metadata.at("data_villager_data"));
    }
#else
    int ZombieVillagerEntity::GetDataVillagerProfessionId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_villager_profession_id"));
    }
#endif


    void ZombieVillagerEntity::SetDataConvertingId(const bool data_converting_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_converting_id"] = data_converting_id;
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    void ZombieVillagerEntity::SetDataVillagerData(const VillagerData& data_villager_data)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_villager_data"] = data_villager_data;
    }
#else
    void ZombieVillagerEntity::SetDataVillagerProfessionId(const int data_villager_profession_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_villager_profession_id"] = data_villager_profession_id;
    }
#endif


    double ZombieVillagerEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double ZombieVillagerEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
