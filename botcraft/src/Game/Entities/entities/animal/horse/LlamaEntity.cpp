#include "botcraft/Game/Entities/entities/animal/horse/LlamaEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, LlamaEntity::metadata_count> LlamaEntity::metadata_names{ {
        "data_strength_id",
        "data_swag_id",
        "data_variant_id",
    } };

    LlamaEntity::LlamaEntity()
    {
        // Initialize all metadata with default values
        SetDataStrengthId(0);
        SetDataSwagId(-1);
        SetDataVariantId(0);
    }

    LlamaEntity::~LlamaEntity()
    {

    }


    std::string LlamaEntity::GetName() const
    {
        return "Llama";
    }

    EntityType LlamaEntity::GetType() const
    {
        return EntityType::Llama;
    }

    double LlamaEntity::GetWidth() const
    {
        return 0.9;
    }

    double LlamaEntity::GetHeight() const
    {
        return 1.87;
    }


    std::string LlamaEntity::GetClassName()
    {
        return "Llama";
    }

    EntityType LlamaEntity::GetClassType()
    {
        return EntityType::Llama;
    }


    nlohmann::json LlamaEntity::Serialize() const
    {
        nlohmann::json output = AbstractChestedHorseEntity::Serialize();

        output["metadata"]["data_strength_id"] = GetDataStrengthId();
        output["metadata"]["data_swag_id"] = GetDataSwagId();
        output["metadata"]["data_variant_id"] = GetDataVariantId();

        return output;
    }


    void LlamaEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractChestedHorseEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int LlamaEntity::GetDataStrengthId() const
    {
        return std::any_cast<int>(metadata.at("data_strength_id"));
    }

    int LlamaEntity::GetDataSwagId() const
    {
        return std::any_cast<int>(metadata.at("data_swag_id"));
    }

    int LlamaEntity::GetDataVariantId() const
    {
        return std::any_cast<int>(metadata.at("data_variant_id"));
    }


    void LlamaEntity::SetDataStrengthId(const int data_strength_id)
    {
        metadata["data_strength_id"] = data_strength_id;
    }

    void LlamaEntity::SetDataSwagId(const int data_swag_id)
    {
        metadata["data_swag_id"] = data_swag_id;
    }

    void LlamaEntity::SetDataVariantId(const int data_variant_id)
    {
        metadata["data_variant_id"] = data_variant_id;
    }

}
