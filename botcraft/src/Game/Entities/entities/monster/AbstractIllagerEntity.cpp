#include "botcraft/Game/Entities/entities/monster/AbstractIllagerEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION < 405 /* < 1.14 */
    const std::array<std::string, AbstractIllagerEntity::metadata_count> AbstractIllagerEntity::metadata_names{ {
        "has_target",
    } };
#endif
    AbstractIllagerEntity::AbstractIllagerEntity()
    {
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        // Initialize all metadata with default values
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


    void AbstractIllagerEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char AbstractIllagerEntity::GetHasTarget() const
    {
        return std::any_cast<char>(metadata.at("has_target"));
    }

    void AbstractIllagerEntity::SetHasTarget(const char has_target)
    {
        metadata["has_target"] = has_target;
    }
#endif

}
