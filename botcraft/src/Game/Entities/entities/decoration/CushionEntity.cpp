#if PROTOCOL_VERSION > 776 /* > 26.2 */
#include "botcraft/Game/Entities/entities/decoration/CushionEntity.hpp"

namespace Botcraft
{
    CushionEntity::CushionEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataColor(0);
    }

    CushionEntity::~CushionEntity()
    {

    }


    std::string CushionEntity::GetName() const
    {
        return "cushion";
    }

    EntityType CushionEntity::GetType() const
    {
        return EntityType::Cushion;
    }


    std::string CushionEntity::GetClassName()
    {
        return "cushion";
    }

    EntityType CushionEntity::GetClassType()
    {
        return EntityType::Cushion;
    }


    ProtocolCraft::Json::Value CushionEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = BlockAttachedEntity::Serialize();

        output["metadata"]["data_color"] = GetDataColor();

        return output;
    }


    int CushionEntity::GetDataColor() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_color"));
    }


    void CushionEntity::SetDataColor(const int data_color)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_color"), data_color);
    }


    double CushionEntity::GetWidthImpl() const
    {
        return 1.0;
    }

    double CushionEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
#endif
