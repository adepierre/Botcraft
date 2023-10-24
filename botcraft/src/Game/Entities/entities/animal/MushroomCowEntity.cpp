#include "botcraft/Game/Entities/entities/animal/MushroomCowEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    const std::array<std::string, MushroomCowEntity::metadata_count> MushroomCowEntity::metadata_names{ {
        "data_type",
    } };
#endif

    MushroomCowEntity::MushroomCowEntity()
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        // Initialize all metadata with default values
        SetDataType("red");
#endif
    }

    MushroomCowEntity::~MushroomCowEntity()
    {

    }


    std::string MushroomCowEntity::GetName() const
    {
        return "mooshroom";
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
        return "mooshroom";
    }

    EntityType MushroomCowEntity::GetClassType()
    {
        return EntityType::MushroomCow;
    }


#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    ProtocolCraft::Json::Value MushroomCowEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = CowEntity::Serialize();

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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    std::string MushroomCowEntity::GetDataType() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<std::string>(metadata.at("data_type"));
    }


    void MushroomCowEntity::SetDataType(const std::string& data_type)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_type"] = data_type;
    }
#endif

}
