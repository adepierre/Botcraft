#if PROTOCOL_VERSION > 477 /* > 1.14 */
#include "botcraft/Game/Entities/entities/npc/villager/AbstractVillagerEntity.hpp"

namespace Botcraft
{
    AbstractVillagerEntity::AbstractVillagerEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataUnhappyCounter(0);
    }

    AbstractVillagerEntity::~AbstractVillagerEntity()
    {

    }

    bool AbstractVillagerEntity::IsAbstractVillager() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractVillagerEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AgeableMobEntity::Serialize();

        output["metadata"]["data_unhappy_counter"] = GetDataUnhappyCounter();

        return output;
    }


    int AbstractVillagerEntity::GetDataUnhappyCounter() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_unhappy_counter"));
    }


    void AbstractVillagerEntity::SetDataUnhappyCounter(const int data_unhappy_counter)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_unhappy_counter"), data_unhappy_counter);
    }

}
#endif
