#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/raid/RaiderEntity.hpp"

namespace Botcraft
{
    RaiderEntity::RaiderEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetIsCelebrating(false);
    }

    RaiderEntity::~RaiderEntity()
    {

    }

    bool RaiderEntity::IsRaider() const
    {
        return true;
    }


    ProtocolCraft::Json::Value RaiderEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = PatrollingMonsterEntity::Serialize();

        output["metadata"]["is_celebrating"] = GetIsCelebrating();

        return output;
    }


    bool RaiderEntity::GetIsCelebrating() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("is_celebrating"));
    }


    void RaiderEntity::SetIsCelebrating(const bool is_celebrating)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("is_celebrating"), is_celebrating);
    }

}
#endif
