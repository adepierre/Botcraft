#if PROTOCOL_VERSION > 754
#include "botcraft/Game/Entities/entities/animal/goat/GoatEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, GoatEntity::metadata_count> GoatEntity::metadata_names{ {
        "data_is_screaming_goat",
    } };

    GoatEntity::GoatEntity()
    {
        // Initialize all metadata with default values
        SetDataIsScreamingGoat(false);
    }

    GoatEntity::~GoatEntity()
    {

    }


    std::string GoatEntity::GetName() const
    {
        return "Goat";
    }

    EntityType GoatEntity::GetType() const
    {
        return EntityType::Goat;
    }

    double GoatEntity::GetWidth() const
    {
        return 0.9;
    }

    double GoatEntity::GetHeight() const
    {
        return 1.3;
    }


    std::string GoatEntity::GetClassName()
    {
        return "Goat";
    }

    EntityType GoatEntity::GetClassType()
    {
        return EntityType::Goat;
    }


    nlohmann::json GoatEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

        output["metadata"]["data_is_screaming_goat"] = GetDataIsScreamingGoat();

        return output;
    }


    void GoatEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool GoatEntity::GetDataIsScreamingGoat() const
    {
        return std::any_cast<bool>(metadata.at("data_is_screaming_goat"));
    }


    void GoatEntity::SetDataIsScreamingGoat(const bool data_is_screaming_goat)
    {
        metadata["data_is_screaming_goat"] = data_is_screaming_goat;
    }

}
#endif
