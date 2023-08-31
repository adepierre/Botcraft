#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/monster/ZoglinEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, ZoglinEntity::metadata_count> ZoglinEntity::metadata_names{ {
        "data_baby_id",
    } };

    ZoglinEntity::ZoglinEntity()
    {
        // Initialize all metadata with default values
        SetDataBabyId(false);
    }

    ZoglinEntity::~ZoglinEntity()
    {

    }


    std::string ZoglinEntity::GetName() const
    {
        return "zoglin";
    }

    EntityType ZoglinEntity::GetType() const
    {
        return EntityType::Zoglin;
    }

    double ZoglinEntity::GetWidth() const
    {
        return 1.3964844;
    }

    double ZoglinEntity::GetHeight() const
    {
        return 1.4;
    }


    std::string ZoglinEntity::GetClassName()
    {
        return "zoglin";
    }

    EntityType ZoglinEntity::GetClassType()
    {
        return EntityType::Zoglin;
    }


    ProtocolCraft::Json::Value ZoglinEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_baby_id"] = GetDataBabyId();

        return output;
    }


    void ZoglinEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool ZoglinEntity::GetDataBabyId() const
    {
        return std::any_cast<bool>(metadata.at("data_baby_id"));
    }


    void ZoglinEntity::SetDataBabyId(const bool data_baby_id)
    {
        metadata["data_baby_id"] = data_baby_id;
    }

}
#endif
