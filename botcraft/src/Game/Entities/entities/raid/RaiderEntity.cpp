#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/raid/RaiderEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, RaiderEntity::metadata_count> RaiderEntity::metadata_names{ {
        "is_celebrating",
    } };

    RaiderEntity::RaiderEntity()
    {
        // Initialize all metadata with default values
        SetIsCelebrating(false);
    }

    RaiderEntity::~RaiderEntity()
    {

    }

    bool RaiderEntity::IsRaider() const
    {
        return true;
    }


    nlohmann::json RaiderEntity::Serialize() const
    {
        nlohmann::json output = PatrollingMonsterEntity::Serialize();

        output["is_celebrating"] = GetIsCelebrating();

        return output;
    }


    void RaiderEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            PatrollingMonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool RaiderEntity::GetIsCelebrating() const
    {
        return std::any_cast<bool>(metadata.at("is_celebrating"));
    }


    void RaiderEntity::SetIsCelebrating(const bool is_celebrating)
    {
        metadata["is_celebrating"] = is_celebrating;
    }

}
#endif
