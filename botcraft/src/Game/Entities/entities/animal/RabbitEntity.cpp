#include "botcraft/Game/Entities/entities/animal/RabbitEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, RabbitEntity::metadata_count> RabbitEntity::metadata_names{ {
        "data_type_id",
    } };

    RabbitEntity::RabbitEntity()
    {
        // Initialize all metadata with default values
        SetDataTypeId(0);
    }

    RabbitEntity::~RabbitEntity()
    {

    }


    std::string RabbitEntity::GetName() const
    {
        return "rabbit";
    }

    EntityType RabbitEntity::GetType() const
    {
        return EntityType::Rabbit;
    }

    double RabbitEntity::GetWidth() const
    {
        return 0.4;
    }

    double RabbitEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string RabbitEntity::GetClassName()
    {
        return "rabbit";
    }

    EntityType RabbitEntity::GetClassType()
    {
        return EntityType::Rabbit;
    }


    ProtocolCraft::Json::Value RabbitEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_type_id"] = GetDataTypeId();

        return output;
    }


    void RabbitEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int RabbitEntity::GetDataTypeId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_type_id"));
    }


    void RabbitEntity::SetDataTypeId(const int data_type_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_type_id"] = data_type_id;
    }

}
