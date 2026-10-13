#include "botcraft/Game/Entities/entities/decoration/painting/PaintingEntity.hpp"

namespace Botcraft
{
    PaintingEntity::PaintingEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
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


    int PaintingEntity::GetDataPaintingVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_painting_variant_id"));
    }


    void PaintingEntity::SetDataPaintingVariantId(const int data_painting_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_painting_variant_id"), data_painting_variant_id);
    }
#endif


    double PaintingEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double PaintingEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
