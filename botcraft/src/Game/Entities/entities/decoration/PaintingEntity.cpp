#include "botcraft/Game/Entities/entities/decoration/PaintingEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    const std::array<std::string, PaintingEntity::metadata_count> PaintingEntity::metadata_names{ {
        "data_painting_variant_id",
    } };
#endif

    PaintingEntity::PaintingEntity()
    {
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        // Initialize all metadata with default values
        SetDataPaintingVariantId(0);
#endif
    }

    PaintingEntity::~PaintingEntity()
    {

    }


    std::string PaintingEntity::GetName() const
    {
        return "painting";
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
        return "painting";
    }

    EntityType PaintingEntity::GetClassType()
    {
        return EntityType::Painting;
    }


#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    ProtocolCraft::Json::Value PaintingEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = HangingEntity::Serialize();

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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const int PaintingEntity::GetDataPaintingVariantId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_painting_variant_id"));
    }


    void PaintingEntity::SetDataPaintingVariantId(const int data_painting_variant_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_painting_variant_id"] = data_painting_variant_id;
    }
#endif
}
