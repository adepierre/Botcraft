#include "botcraft/Game/Entities/entities/AgeableMobEntity.hpp"

namespace Botcraft
{
    AgeableMobEntity::AgeableMobEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataBabyId(false);
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        SetAgeLocked(false);
#endif
    }

    AgeableMobEntity::~AgeableMobEntity()
    {

    }

    bool AgeableMobEntity::IsAgeableMob() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AgeableMobEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = PathfinderMobEntity::Serialize();

        output["metadata"]["data_baby_id"] = GetDataBabyId();
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        output["metadata"]["age_locked"] = GetAgeLocked();
#endif

        return output;
    }


    bool AgeableMobEntity::GetDataBabyId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_baby_id"));
    }

#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    bool AgeableMobEntity::GetAgeLocked() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("age_locked"));
    }
#endif


    void AgeableMobEntity::SetDataBabyId(const bool data_baby_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_baby_id"), data_baby_id);
    }

#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    void AgeableMobEntity::SetAgeLocked(const bool age_locked)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("age_locked"), age_locked);
    }
#endif

}
