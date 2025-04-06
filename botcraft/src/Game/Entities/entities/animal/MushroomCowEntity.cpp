#include "botcraft/Game/Entities/entities/animal/MushroomCowEntity.hpp"

#include <mutex>

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
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SetDataType("red");
#else
        SetDataType(0);
#endif
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
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        ProtocolCraft::Json::Value output = CowEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = AbstractCowEntity::Serialize();
#endif

        output["metadata"]["data_type"] = GetDataType();

        return output;
    }


    void MushroomCowEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            CowEntity::SetMetadataValue(index, value);
#else
            AbstractCowEntity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
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
#else
    int MushroomCowEntity::GetDataType() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_type"));
    }


    void MushroomCowEntity::SetDataType(const int data_type)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_type"] = data_type;
    }
#endif
#endif


    double MushroomCowEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double MushroomCowEntity::GetHeightImpl() const
    {
        return 1.4;
    }

}
