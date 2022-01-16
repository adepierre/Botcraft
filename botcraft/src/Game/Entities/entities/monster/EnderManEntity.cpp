#include "botcraft/Game/Entities/entities/monster/EnderManEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, EnderManEntity::metadata_count> EnderManEntity::metadata_names{ {
        "data_carry_state",
        "data_creepy",
#if PROTOCOL_VERSION > 498
        "data_stared_at",
#endif
    } };

    EnderManEntity::EnderManEntity()
    {
        // Initialize all metadata with default values
        SetDataCarryState(0);
        SetDataCreepy(false);
#if PROTOCOL_VERSION > 498
        SetDataStaredAt(false);
#endif
    }

    EnderManEntity::~EnderManEntity()
    {

    }


    std::string EnderManEntity::GetName() const
    {
        return "EnderMan";
    }

    EntityType EnderManEntity::GetType() const
    {
        return EntityType::EnderMan;
    }

    double EnderManEntity::GetWidth() const
    {
        return 0.6;
    }

    double EnderManEntity::GetHeight() const
    {
        return 2.9;
    }


    std::string EnderManEntity::GetClassName()
    {
        return "EnderMan";
    }

    EntityType EnderManEntity::GetClassType()
    {
        return EntityType::EnderMan;
    }


    nlohmann::json EnderManEntity::Serialize() const
    {
        nlohmann::json output = MonsterEntity::Serialize();

        output["metadata"]["data_carry_state"] = GetDataCarryState();
        output["metadata"]["data_creepy"] = GetDataCreepy();
#if PROTOCOL_VERSION > 498
        output["metadata"]["data_stared_at"] = GetDataStaredAt();
#endif

        return output;
    }


    void EnderManEntity::SetMetadataValue(const int index, const std::any& value)
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

    int EnderManEntity::GetDataCarryState() const
    {
        return std::any_cast<int>(metadata.at("data_carry_state"));
    }

    bool EnderManEntity::GetDataCreepy() const
    {
        return std::any_cast<bool>(metadata.at("data_creepy"));
    }

#if PROTOCOL_VERSION > 498
    bool EnderManEntity::GetDataStaredAt() const
    {
        return std::any_cast<bool>(metadata.at("data_stared_at"));
    }
#endif


    void EnderManEntity::SetDataCarryState(const int data_carry_state)
    {
        metadata["data_carry_state"] = data_carry_state;
    }

    void EnderManEntity::SetDataCreepy(const bool data_creepy)
    {
        metadata["data_creepy"] = data_creepy;
    }

#if PROTOCOL_VERSION > 498
    void EnderManEntity::SetDataStaredAt(const bool data_stared_at)
    {
        metadata["data_stared_at"] = data_stared_at;
    }
#endif

}
