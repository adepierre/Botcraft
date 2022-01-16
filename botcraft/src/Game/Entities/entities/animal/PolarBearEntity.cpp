#include "botcraft/Game/Entities/entities/animal/PolarBearEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, PolarBearEntity::metadata_count> PolarBearEntity::metadata_names{ {
        "data_standing_id",
    } };

    PolarBearEntity::PolarBearEntity()
    {
        // Initialize all metadata with default values
        SetDataStandingId(false);
    }

    PolarBearEntity::~PolarBearEntity()
    {

    }


    std::string PolarBearEntity::GetName() const
    {
        return "PolarBear";
    }

    EntityType PolarBearEntity::GetType() const
    {
        return EntityType::PolarBear;
    }

    double PolarBearEntity::GetWidth() const
    {
#if PROTOCOL_VERSION > 404
        return 1.4;
#else
        return 1.3;
#endif
    }

    double PolarBearEntity::GetHeight() const
    {
        return 1.4;
    }


    std::string PolarBearEntity::GetClassName()
    {
        return "PolarBear";
    }

    EntityType PolarBearEntity::GetClassType()
    {
        return EntityType::PolarBear;
    }


    nlohmann::json PolarBearEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

        output["metadata"]["data_standing_id"] = GetDataStandingId();

        return output;
    }


    void PolarBearEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool PolarBearEntity::GetDataStandingId() const
    {
        return std::any_cast<bool>(metadata.at("data_standing_id"));
    }


    void PolarBearEntity::SetDataStandingId(const bool data_standing_id)
    {
        metadata["data_standing_id"] = data_standing_id;
    }

}
