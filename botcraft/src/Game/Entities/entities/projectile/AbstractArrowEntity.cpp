#include "botcraft/Game/Entities/entities/projectile/AbstractArrowEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, AbstractArrowEntity::metadata_count> AbstractArrowEntity::metadata_names{ {
        "id_flags",
#if PROTOCOL_VERSION < 579 && PROTOCOL_VERSION > 393
        "data_owneruuid_id",
#endif
#if PROTOCOL_VERSION > 404
        "pierce_level",
#endif
    } };

    AbstractArrowEntity::AbstractArrowEntity()
    {
        // Initialize all metadata with default values
        SetIdFlags(0);
#if PROTOCOL_VERSION < 579 && PROTOCOL_VERSION > 393
        SetDataOwneruuidId(std::optional<ProtocolCraft::UUID>());
#endif
#if PROTOCOL_VERSION > 404
        SetPierceLevel(0);
#endif
    }

    AbstractArrowEntity::~AbstractArrowEntity()
    {

    }

    bool AbstractArrowEntity::IsAbstractArrow() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractArrowEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 578
        ProtocolCraft::Json::Value output = ProjectileEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = Entity::Serialize();
#endif

        output["metadata"]["id_flags"] = GetIdFlags();
#if PROTOCOL_VERSION < 579 && PROTOCOL_VERSION > 393
        output["metadata"]["data_owneruuid_id"] = GetDataOwneruuidId() ? ProtocolCraft::Json::Value(GetDataOwneruuidId().value()) : ProtocolCraft::Json::Value();
#endif
#if PROTOCOL_VERSION > 404
        output["metadata"]["pierce_level"] = GetPierceLevel();
#endif

        return output;
    }


    void AbstractArrowEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION > 578
            ProjectileEntity::SetMetadataValue(index, value);
#else
            Entity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char AbstractArrowEntity::GetIdFlags() const
    {
        return std::any_cast<char>(metadata.at("id_flags"));
    }

#if PROTOCOL_VERSION < 579 && PROTOCOL_VERSION > 393
    const std::optional<ProtocolCraft::UUID>& AbstractArrowEntity::GetDataOwneruuidId() const
    {
        return std::any_cast<const std::optional<ProtocolCraft::UUID>&>(metadata.at("data_owneruuid_id"));
    }
#endif

#if PROTOCOL_VERSION > 404
    char AbstractArrowEntity::GetPierceLevel() const
    {
        return std::any_cast<char>(metadata.at("pierce_level"));
    }
#endif


    void AbstractArrowEntity::SetIdFlags(const char id_flags)
    {
        metadata["id_flags"] = id_flags;
    }

#if PROTOCOL_VERSION < 579 && PROTOCOL_VERSION > 393
    void AbstractArrowEntity::SetDataOwneruuidId(const std::optional<ProtocolCraft::UUID>& data_owneruuid_id)
    {
        metadata["data_owneruuid_id"] = data_owneruuid_id;
    }
#endif

#if PROTOCOL_VERSION > 404
    void AbstractArrowEntity::SetPierceLevel(const char pierce_level)
    {
        metadata["pierce_level"] = pierce_level;
    }
#endif

}
