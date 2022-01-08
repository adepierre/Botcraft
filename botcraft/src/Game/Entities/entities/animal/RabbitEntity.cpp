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
        return "Rabbit";
    }

    EntityType RabbitEntity::GetType() const
    {
        return EntityType::Rabbit;
    }

    AABB RabbitEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
        return "Rabbit";
    }

    EntityType RabbitEntity::GetClassType()
    {
        return EntityType::Rabbit;
    }


    nlohmann::json RabbitEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int RabbitEntity::GetDataTypeId() const
    {
        return std::any_cast<int>(metadata.at("data_type_id"));
    }


    void RabbitEntity::SetDataTypeId(const int data_type_id)
    {
        metadata["data_type_id"] = data_type_id;
    }

}
