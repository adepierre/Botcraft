#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
#include "botcraft/Game/Entities/entities/monster/piglin/AbstractPiglinEntity.hpp"

namespace Botcraft
{
    AbstractPiglinEntity::AbstractPiglinEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataImmuneToZombification(false);
    }

    AbstractPiglinEntity::~AbstractPiglinEntity()
    {

    }

    bool AbstractPiglinEntity::IsAbstractPiglin() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractPiglinEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_immune_to_zombification"] = GetDataImmuneToZombification();

        return output;
    }


    bool AbstractPiglinEntity::GetDataImmuneToZombification() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_immune_to_zombification"));
    }


    void AbstractPiglinEntity::SetDataImmuneToZombification(const bool data_immune_to_zombification)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_immune_to_zombification"), data_immune_to_zombification);
    }

}
#endif
