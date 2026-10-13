#include "botcraft/Game/Entities/entities/npc/villager/VillagerEntity.hpp"

namespace Botcraft
{
    VillagerEntity::VillagerEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        SetDataVillagerData(VillagerData{ 2, 0, 1 });
#else
        SetDataVillagerProfessionId(0);
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        SetDataVillagerDataFinalized(false);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.5) });
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 48.0) });
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
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        output["metadata"]["data_villager_data_finalized"] = GetDataVillagerDataFinalized();
#endif

        return output;
    }


#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    VillagerData VillagerEntity::GetDataVillagerData() const
    {
        return GetMetadata<VillagerData>(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_data"));
    }
#else
    int VillagerEntity::GetDataVillagerProfessionId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_profession_id"));
    }
#endif

#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    bool VillagerEntity::GetDataVillagerDataFinalized() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_data_finalized"));
    }
#endif


#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    void VillagerEntity::SetDataVillagerData(const VillagerData& data_villager_data)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_data"), data_villager_data);
    }
#else
    void VillagerEntity::SetDataVillagerProfessionId(const int data_villager_profession_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_profession_id"), data_villager_profession_id);
    }
#endif

#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    void VillagerEntity::SetDataVillagerDataFinalized(const bool data_villager_data_finalized)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_villager_data_finalized"), data_villager_data_finalized);
    }
#endif


    double VillagerEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double VillagerEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
