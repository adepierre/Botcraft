#include "botcraft/Game/Entities/entities/animal/equine/LlamaEntity.hpp"

namespace Botcraft
{
    LlamaEntity::LlamaEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataStrengthId(0);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SetDataSwagId(-1);
#endif
        SetDataVariantId(0);

        // Initialize all attributes with default values
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 40.0) });
#endif
    }

    LlamaEntity::~LlamaEntity()
    {

    }


    std::string LlamaEntity::GetName() const
    {
        return "llama";
    }

    EntityType LlamaEntity::GetType() const
    {
        return EntityType::Llama;
    }


    std::string LlamaEntity::GetClassName()
    {
        return "llama";
    }

    EntityType LlamaEntity::GetClassType()
    {
        return EntityType::Llama;
    }


    ProtocolCraft::Json::Value LlamaEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractChestedHorseEntity::Serialize();

        output["metadata"]["data_strength_id"] = GetDataStrengthId();
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        output["metadata"]["data_swag_id"] = GetDataSwagId();
#endif
        output["metadata"]["data_variant_id"] = GetDataVariantId();

        return output;
    }


    int LlamaEntity::GetDataStrengthId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_strength_id"));
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    int LlamaEntity::GetDataSwagId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_swag_id"));
    }
#endif

    int LlamaEntity::GetDataVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"));
    }


    void LlamaEntity::SetDataStrengthId(const int data_strength_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_strength_id"), data_strength_id);
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    void LlamaEntity::SetDataSwagId(const int data_swag_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_swag_id"), data_swag_id);
    }
#endif

    void LlamaEntity::SetDataVariantId(const int data_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"), data_variant_id);
    }


    double LlamaEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double LlamaEntity::GetHeightImpl() const
    {
        return 1.87;
    }

}
