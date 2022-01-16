#include "botcraft/Game/Entities/entities/animal/MushroomCowEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION > 404
    const std::array<std::string, MushroomCowEntity::metadata_count> MushroomCowEntity::metadata_names{ {
        "data_type",
    } };
#endif

    MushroomCowEntity::MushroomCowEntity()
    {
#if PROTOCOL_VERSION > 404
        // Initialize all metadata with default values
        SetDataType("red");
#endif
    }

    MushroomCowEntity::~MushroomCowEntity()
    {

    }


    std::string MushroomCowEntity::GetName() const
    {
        return "MushroomCow";
    }

    EntityType MushroomCowEntity::GetType() const
    {
        return EntityType::MushroomCow;
    }

    double MushroomCowEntity::GetWidth() const
    {
        return 0.9;
    }

    double MushroomCowEntity::GetHeight() const
    {
        return 1.4;
    }


    std::string MushroomCowEntity::GetClassName()
    {
        return "MushroomCow";
    }

    EntityType MushroomCowEntity::GetClassType()
    {
        return EntityType::MushroomCow;
    }


#if PROTOCOL_VERSION > 404
    nlohmann::json MushroomCowEntity::Serialize() const
    {
        nlohmann::json output = CowEntity::Serialize();

        output["metadata"]["data_type"] = GetDataType();

        return output;
    }


    void MushroomCowEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            CowEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const std::string& MushroomCowEntity::GetDataType() const
    {
        return std::any_cast<const std::string&>(metadata.at("data_type"));
    }


    void MushroomCowEntity::SetDataType(const std::string& data_type)
    {
        metadata["data_type"] = data_type;
    }
#endif

}
