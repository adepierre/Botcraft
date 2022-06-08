#if PROTOCOL_VERSION > 758
#include "botcraft/Game/Entities/entities/monster/warden/WardenEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, WardenEntity::metadata_count> WardenEntity::metadata_names{ {
        "client_anger_level",
    } };

    WardenEntity::WardenEntity()
    {
        // Initialize all metadata with default values
        SetClientAngerLevel(0);
    }

    WardenEntity::~WardenEntity()
    {

    }


    std::string WardenEntity::GetName() const
    {
        return "Warden";
    }

    EntityType WardenEntity::GetType() const
    {
        return EntityType::Warden;
    }

    double WardenEntity::GetWidth() const
    {
        return 0.9;
    }

    double WardenEntity::GetHeight() const
    {
        return 2.9;
    }


    std::string WardenEntity::GetClassName()
    {
        return "Warden";
    }

    EntityType WardenEntity::GetClassType()
    {
        return EntityType::Warden;
    }


    nlohmann::json WardenEntity::Serialize() const
    {
        nlohmann::json output = MonsterEntity::Serialize();

        output["client_anger_level"] = GetClientAngerLevel();

        return output;
    }


    void WardenEntity::SetMetadataValue(const int index, const std::any& value)
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

    int WardenEntity::GetClientAngerLevel() const
    {
        return std::any_cast<int>(metadata.at("client_anger_level"));
    }


    void WardenEntity::SetClientAngerLevel(const int client_anger_level)
    {
        metadata["client_anger_level"] = client_anger_level;
    }

}
#endif
