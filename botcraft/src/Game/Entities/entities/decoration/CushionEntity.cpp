#if PROTOCOL_VERSION > 776 /* > 26.2 */
#include "botcraft/Game/Entities/entities/decoration/CushionEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, CushionEntity::metadata_count> CushionEntity::metadata_names{ {
        "data_color",
    } };

    CushionEntity::CushionEntity()
    {
        // Initialize all metadata with default values
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


    void CushionEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            BlockAttachedEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }


    int CushionEntity::GetDataColor() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_color"));
    }


    void CushionEntity::SetDataColor(const int data_color)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_color"] = data_color;
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
