#include "botcraft/Game/Entities/entities/animal/horse/AbstractHorseEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, AbstractHorseEntity::metadata_count> AbstractHorseEntity::metadata_names{ {
        "data_id_flags",
        "data_id_owner_uuid",
    } };

    AbstractHorseEntity::AbstractHorseEntity()
    {
        // Initialize all metadata with default values
        SetDataIdFlags(0);
        SetDataIdOwnerUuid(std::optional<ProtocolCraft::UUID>());
    }

    AbstractHorseEntity::~AbstractHorseEntity()
    {

    }

    bool AbstractHorseEntity::IsAbstractHorse() const
    {
        return true;
    }


    nlohmann::json AbstractHorseEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

        output["data_id_flags"] = GetDataIdFlags();
        output["data_id_owner_uuid"] = GetDataIdOwnerUuid() ? nlohmann::json(GetDataIdOwnerUuid().value()) : nlohmann::json();

        return output;
    }


    void AbstractHorseEntity::SetMetadataValue(const int index, const std::any& value)
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

    char AbstractHorseEntity::GetDataIdFlags() const
    {
        return std::any_cast<char>(metadata.at("data_id_flags"));
    }

    const std::optional<ProtocolCraft::UUID>& AbstractHorseEntity::GetDataIdOwnerUuid() const
    {
        return std::any_cast<const std::optional<ProtocolCraft::UUID>&>(metadata.at("data_id_owner_uuid"));
    }


    void AbstractHorseEntity::SetDataIdFlags(const char data_id_flags)
    {
        metadata["data_id_flags"] = data_id_flags;
    }

    void AbstractHorseEntity::SetDataIdOwnerUuid(const std::optional<ProtocolCraft::UUID>& data_id_owner_uuid)
    {
        metadata["data_id_owner_uuid"] = data_id_owner_uuid;
    }

}
