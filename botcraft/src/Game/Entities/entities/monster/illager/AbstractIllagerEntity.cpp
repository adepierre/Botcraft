#include "botcraft/Game/Entities/entities/monster/illager/AbstractIllagerEntity.hpp"

namespace Botcraft
{
    AbstractIllagerEntity::AbstractIllagerEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        SetHasTarget(0);
#endif
    }

    AbstractIllagerEntity::~AbstractIllagerEntity()
    {

    }

    bool AbstractIllagerEntity::IsAbstractIllager() const
    {
        return true;
    }


#if PROTOCOL_VERSION < 405 /* < 1.14 */
    ProtocolCraft::Json::Value AbstractIllagerEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["has_target"] = GetHasTarget();

        return output;
    }


    char AbstractIllagerEntity::GetHasTarget() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("has_target"));
    }

    void AbstractIllagerEntity::SetHasTarget(const char has_target)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("has_target"), has_target);
    }
#endif

}
