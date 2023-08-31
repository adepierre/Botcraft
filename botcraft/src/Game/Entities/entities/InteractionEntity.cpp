#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "botcraft/Game/Entities/entities/InteractionEntity.hpp"

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

    double InteractionEntity::GetWidth() const
    {
        return 0.0;
    }

    double InteractionEntity::GetHeight() const
    {
        return 0.0;
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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    
    float InteractionEntity::GetDataWidthId() const
    {
        return std::any_cast<float>(metadata.at("data_width_id"));
    }
    
    float InteractionEntity::GetDataHeightId() const
    {
        return std::any_cast<float>(metadata.at("data_height_id"));
    }
    
    bool InteractionEntity::GetDataResponseId() const
    {
        return std::any_cast<bool>(metadata.at("data_response_id"));
    }
    
    
    void InteractionEntity::SetDataWidthId(const float data_width_id)
    {
        metadata["data_width_id"] = data_width_id;
    }
    
    void InteractionEntity::SetDataHeightId(const float data_height_id)
    {
        metadata["data_height_id"] = data_height_id;
    }
    
    void InteractionEntity::SetDataResponseId(const bool data_response_id)
    {
        metadata["data_response_id"] = data_response_id;
    }
    

}
#endif
