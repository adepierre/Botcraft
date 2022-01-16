#include "botcraft/Game/Entities/entities/animal/OcelotEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, OcelotEntity::metadata_count> OcelotEntity::metadata_names{ {
#if PROTOCOL_VERSION > 404
        "data_trusting",
#else
        "data_type_id",
#endif
    } };

    OcelotEntity::OcelotEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION > 404
        SetDataTrusting(false);
#else
        SetDataTypeId(0);
#endif
    }

    OcelotEntity::~OcelotEntity()
    {

    }


    std::string OcelotEntity::GetName() const
    {
        return "Ocelot";
    }

    EntityType OcelotEntity::GetType() const
    {
        return EntityType::Ocelot;
    }

    double OcelotEntity::GetWidth() const
    {
        return 0.6;
    }

    double OcelotEntity::GetHeight() const
    {
        return 0.7;
    }


    std::string OcelotEntity::GetClassName()
    {
        return "Ocelot";
    }

    EntityType OcelotEntity::GetClassType()
    {
        return EntityType::Ocelot;
    }


    nlohmann::json OcelotEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

#if PROTOCOL_VERSION > 404
        output["metadata"]["data_trusting"] = GetDataTrusting();
#else
        output["metadata"]["data_type_id"] = GetDataTypeId();
#endif

        return output;
    }


    void OcelotEntity::SetMetadataValue(const int index, const std::any& value)
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

#if PROTOCOL_VERSION > 404
    bool OcelotEntity::GetDataTrusting() const
    {
        return std::any_cast<bool>(metadata.at("data_trusting"));
    }


    void OcelotEntity::SetDataTrusting(const bool data_trusting)
    {
        metadata["data_trusting"] = data_trusting;
    }
#else
    int OcelotEntity::GetDataTypeId() const
    {
        return std::any_cast<int>(metadata.at("data_type_id"));
    }


    void OcelotEntity::SetDataTypeId(const int data_type_id)
    {
        metadata["data_type_id"] = data_type_id;
    }
#endif

}
