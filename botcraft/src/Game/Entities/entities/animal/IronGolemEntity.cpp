#include "botcraft/Game/Entities/entities/animal/IronGolemEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, IronGolemEntity::metadata_count> IronGolemEntity::metadata_names{ {
        "data_flags_id",
    } };

    IronGolemEntity::IronGolemEntity()
    {
        // Initialize all metadata with default values
        SetDataFlagsId(0);
    }

    IronGolemEntity::~IronGolemEntity()
    {

    }


    std::string IronGolemEntity::GetName() const
    {
        return "iron_golem";
    }

    EntityType IronGolemEntity::GetType() const
    {
        return EntityType::IronGolem;
    }

    double IronGolemEntity::GetWidth() const
    {
        return 1.4;
    }

    double IronGolemEntity::GetHeight() const
    {
        return 2.7;
    }


    std::string IronGolemEntity::GetClassName()
    {
        return "iron_golem";
    }

    EntityType IronGolemEntity::GetClassType()
    {
        return EntityType::IronGolem;
    }


    ProtocolCraft::Json::Value IronGolemEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractGolemEntity::Serialize();

        output["metadata"]["data_flags_id"] = GetDataFlagsId();

        return output;
    }


    void IronGolemEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractGolemEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char IronGolemEntity::GetDataFlagsId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }


    void IronGolemEntity::SetDataFlagsId(const char data_flags_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_flags_id"] = data_flags_id;
    }

}
