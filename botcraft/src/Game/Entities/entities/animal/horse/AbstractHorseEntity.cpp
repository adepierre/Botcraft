#include "botcraft/Game/Entities/entities/animal/horse/AbstractHorseEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, AbstractHorseEntity::metadata_count> AbstractHorseEntity::metadata_names{ {
        "data_id_flags",
#if PROTOCOL_VERSION < 762
        "data_id_owner_uuid",
#endif
    } };

    AbstractHorseEntity::AbstractHorseEntity()
    {
        // Initialize all metadata with default values
        SetDataIdFlags(0);
#if PROTOCOL_VERSION < 762
        SetDataIdOwnerUuid(std::optional<ProtocolCraft::UUID>());
#endif
    }

    AbstractHorseEntity::~AbstractHorseEntity()
    {

    }

    bool AbstractHorseEntity::IsAbstractHorse() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractHorseEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_id_flags"] = GetDataIdFlags();
#if PROTOCOL_VERSION < 762
        output["metadata"]["data_id_owner_uuid"] = GetDataIdOwnerUuid() ? ProtocolCraft::Json::Value(GetDataIdOwnerUuid().value()) : ProtocolCraft::Json::Value();
#endif

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

#if PROTOCOL_VERSION < 762
    const std::optional<ProtocolCraft::UUID>& AbstractHorseEntity::GetDataIdOwnerUuid() const
    {
        return std::any_cast<const std::optional<ProtocolCraft::UUID>&>(metadata.at("data_id_owner_uuid"));
    }
#endif


    void AbstractHorseEntity::SetDataIdFlags(const char data_id_flags)
    {
        metadata["data_id_flags"] = data_id_flags;
    }

#if PROTOCOL_VERSION < 762
    void AbstractHorseEntity::SetDataIdOwnerUuid(const std::optional<ProtocolCraft::UUID>& data_id_owner_uuid)
    {
        metadata["data_id_owner_uuid"] = data_id_owner_uuid;
    }
#endif

}
