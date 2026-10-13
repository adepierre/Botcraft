#include "botcraft/Game/Entities/entities/monster/zombie/ZombieVillagerEntity.hpp"

namespace Botcraft
{
    ZombieVillagerEntity::ZombieVillagerEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataConvertingId(false);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        SetDataVillagerData(VillagerData{ 2, 0, 1 }); // TODO: from 1.21.9 it's a random profession and a type depending on the biome, but we don't really care on the clientside I guess
#else
        SetDataVillagerProfessionId(0);
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        SetDataVillagerDataFinalized(false);
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
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        output["metadata"]["data_villager_data_finalized"] = GetDataVillagerDataFinalized();
#endif

        return output;
    }


    bool ZombieVillagerEntity::GetDataConvertingId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_converting_id"));
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    VillagerData ZombieVillagerEntity::GetDataVillagerData() const
    {
        return GetMetadata<VillagerData>(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_data"));
    }
#else
    int ZombieVillagerEntity::GetDataVillagerProfessionId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_profession_id"));
    }
#endif

#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    bool ZombieVillagerEntity::GetDataVillagerDataFinalized() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_data_finalized"));
    }
#endif


    void ZombieVillagerEntity::SetDataConvertingId(const bool data_converting_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_converting_id"), data_converting_id);
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    void ZombieVillagerEntity::SetDataVillagerData(const VillagerData& data_villager_data)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_data"), data_villager_data);
    }
#else
    void ZombieVillagerEntity::SetDataVillagerProfessionId(const int data_villager_profession_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_profession_id"), data_villager_profession_id);
    }
#endif

#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    void ZombieVillagerEntity::SetDataVillagerDataFinalized(const bool data_villager_data_finalized)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_data_finalized"), data_villager_data_finalized);
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
