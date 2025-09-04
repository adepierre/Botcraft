#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "botcraft/Game/Entities/entities/InteractionEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, InteractionEntity::metadata_count> InteractionEntity::metadata_names{ {
        "data_width_id",
        "data_height_id",
        "data_response_id",
    } };

    InteractionEntity::InteractionEntity()
    {
        // Initialize all metadata with default values
        SetDataWidthId(1.0f);
        SetDataHeightId(1.0f);
        SetDataResponseId(false);
    }

    InteractionEntity::~InteractionEntity()
    {

    }


    std::string InteractionEntity::GetName() const
    {
        return "interaction";
    }

    EntityType InteractionEntity::GetType() const
    {
        return EntityType::Interaction;
    }


    std::string InteractionEntity::GetClassName()
    {
        return "interaction";
    }

    EntityType InteractionEntity::GetClassType()
    {
        return EntityType::Interaction;
    }



    ProtocolCraft::Json::Value InteractionEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_width_id"] = GetDataWidthId();
        output["metadata"]["data_height_id"] = GetDataHeightId();
        output["metadata"]["data_response_id"] = GetDataResponseId();

        return output;
    }


    void InteractionEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }


    float InteractionEntity::GetDataWidthId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_width_id"));
    }

    float InteractionEntity::GetDataHeightId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_height_id"));
    }

    bool InteractionEntity::GetDataResponseId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_response_id"));
    }


    void InteractionEntity::SetDataWidthId(const float data_width_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_width_id"] = data_width_id;
    }

    void InteractionEntity::SetDataHeightId(const float data_height_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_height_id"] = data_height_id;
    }

    void InteractionEntity::SetDataResponseId(const bool data_response_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_response_id"] = data_response_id;
    }


    double InteractionEntity::GetWidthImpl() const
    {
        return 0.0;
    }

    double InteractionEntity::GetHeightImpl() const
    {
        return 0.0;
    }

}
#endif
