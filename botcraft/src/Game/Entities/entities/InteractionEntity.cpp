#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "botcraft/Game/Entities/entities/InteractionEntity.hpp"

namespace Botcraft
{
    InteractionEntity::InteractionEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    float InteractionEntity::GetDataWidthId() const
    {
        return GetMetadata<float>(BOTCRAFT_ENTITY_METADATA_INDEX("data_width_id"));
    }

    float InteractionEntity::GetDataHeightId() const
    {
        return GetMetadata<float>(BOTCRAFT_ENTITY_METADATA_INDEX("data_height_id"));
    }

    bool InteractionEntity::GetDataResponseId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_response_id"));
    }


    void InteractionEntity::SetDataWidthId(const float data_width_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_width_id"), data_width_id);
    }

    void InteractionEntity::SetDataHeightId(const float data_height_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_height_id"), data_height_id);
    }

    void InteractionEntity::SetDataResponseId(const bool data_response_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_response_id"), data_response_id);
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
