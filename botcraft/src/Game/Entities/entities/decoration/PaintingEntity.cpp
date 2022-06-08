#include "botcraft/Game/Entities/entities/decoration/PaintingEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION > 758
    const std::array<std::string, PaintingEntity::metadata_count> PaintingEntity::metadata_names{ {
        "data_painting_variant_id",
    } };
#endif

    PaintingEntity::PaintingEntity()
    {
#if PROTOCOL_VERSION > 758
        // Initialize all metadata with default values
        SetDataPaintingVariantId(0);
#endif
    }

    PaintingEntity::~PaintingEntity()
    {

    }


    std::string PaintingEntity::GetName() const
    {
        return "Painting";
    }

    EntityType PaintingEntity::GetType() const
    {
        return EntityType::Painting;
    }

    double PaintingEntity::GetWidth() const
    {
        return 0.5;
    }

    double PaintingEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string PaintingEntity::GetClassName()
    {
        return "Painting";
    }

    EntityType PaintingEntity::GetClassType()
    {
        return EntityType::Painting;
    }


#if PROTOCOL_VERSION > 758
    nlohmann::json PaintingEntity::Serialize() const
    {
        nlohmann::json output = HangingEntity::Serialize();

        output["metadata"]["data_painting_variant_id"] = GetDataPaintingVariantId();

        return output;
    }


    void PaintingEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            HangingEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const int PaintingEntity::GetDataPaintingVariantId() const
    {
        return std::any_cast<int>(metadata.at("data_painting_variant_id"));
    }


    void PaintingEntity::SetDataPaintingVariantId(const int data_painting_variant_id)
    {
        metadata["data_painting_variant_id"] = data_painting_variant_id;
    }
#endif
}
