#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/animal/CatEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, CatEntity::metadata_count> CatEntity::metadata_names{ {
        "data_type_id",
        "is_lying",
        "relax_state_one",
        "data_collar_color",
    } };

    CatEntity::CatEntity()
    {
        // Initialize all metadata with default values
        SetDataTypeId(1);
        SetIsLying(false);
        SetRelaxStateOne(false);
        SetDataCollarColor(14);
    }

    CatEntity::~CatEntity()
    {

    }


    std::string CatEntity::GetName() const
    {
        return "cat";
    }

    EntityType CatEntity::GetType() const
    {
        return EntityType::Cat;
    }

    double CatEntity::GetWidth() const
    {
        return 0.6;
    }

    double CatEntity::GetHeight() const
    {
        return 0.7;
    }


    std::string CatEntity::GetClassName()
    {
        return "cat";
    }

    EntityType CatEntity::GetClassType()
    {
        return EntityType::Cat;
    }


    ProtocolCraft::Json::Value CatEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = TamableAnimalEntity::Serialize();

        output["metadata"]["data_type_id"] = GetDataTypeId();
        output["metadata"]["is_lying"] = GetIsLying();
        output["metadata"]["relax_state_one"] = GetRelaxStateOne();
        output["metadata"]["data_collar_color"] = GetDataCollarColor();

        return output;
    }


    void CatEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            TamableAnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int CatEntity::GetDataTypeId() const
    {
        return std::any_cast<int>(metadata.at("data_type_id"));
    }

    bool CatEntity::GetIsLying() const
    {
        return std::any_cast<bool>(metadata.at("is_lying"));
    }

    bool CatEntity::GetRelaxStateOne() const
    {
        return std::any_cast<bool>(metadata.at("relax_state_one"));
    }

    int CatEntity::GetDataCollarColor() const
    {
        return std::any_cast<int>(metadata.at("data_collar_color"));
    }


    void CatEntity::SetDataTypeId(const int data_type_id)
    {
        metadata["data_type_id"] = data_type_id;
    }

    void CatEntity::SetIsLying(const bool is_lying)
    {
        metadata["is_lying"] = is_lying;
    }

    void CatEntity::SetRelaxStateOne(const bool relax_state_one)
    {
        metadata["relax_state_one"] = relax_state_one;
    }

    void CatEntity::SetDataCollarColor(const int data_collar_color)
    {
        metadata["data_collar_color"] = data_collar_color;
    }

}
#endif
