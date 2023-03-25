#if PROTOCOL_VERSION > 754
#include "botcraft/Game/Entities/entities/animal/goat/GoatEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, GoatEntity::metadata_count> GoatEntity::metadata_names{ {
        "data_is_screaming_goat",
#if PROTOCOL_VERSION > 758
        "data_has_left_horn",
        "data_has_right_horn",
#endif
    } };

    GoatEntity::GoatEntity()
    {
        // Initialize all metadata with default values
        SetDataIsScreamingGoat(false);
#if PROTOCOL_VERSION > 758
        SetDataHasLeftHorn(true);
        SetDataHasRightHorn(true);
#endif
    }

    GoatEntity::~GoatEntity()
    {

    }


    std::string GoatEntity::GetName() const
    {
        return "goat";
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
        return "goat";
    }

    EntityType GoatEntity::GetClassType()
    {
        return EntityType::Goat;
    }


    ProtocolCraft::Json::Value GoatEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_is_screaming_goat"] = GetDataIsScreamingGoat();
#if PROTOCOL_VERSION > 758
        output["metadata"]["data_has_left_horn"] = GetDataHasLeftHorn();
        output["metadata"]["data_has_right_horn"] = GetDataHasRightHorn();
#endif

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

#if PROTOCOL_VERSION > 758
    bool GoatEntity::GetDataHasLeftHorn() const
    {
        return std::any_cast<bool>(metadata.at("data_has_left_horn"));
    }

    bool GoatEntity::GetDataHasRightHorn() const
    {
        return std::any_cast<bool>(metadata.at("data_has_right_horn"));
    }
#endif


    void GoatEntity::SetDataIsScreamingGoat(const bool data_is_screaming_goat)
    {
        metadata["data_is_screaming_goat"] = data_is_screaming_goat;
    }

#if PROTOCOL_VERSION > 758
    void GoatEntity::SetDataHasLeftHorn(const bool data_has_left_horn)
    {
        metadata["data_has_left_horn"] = data_has_left_horn;
    }

    void GoatEntity::SetDataHasRightHorn(const bool data_has_right_horn)
    {
        metadata["data_has_right_horn"] = data_has_right_horn;
    }
#endif

}
#endif
