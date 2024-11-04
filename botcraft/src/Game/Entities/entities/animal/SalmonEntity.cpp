#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/animal/SalmonEntity.hpp"

#include <mutex>

namespace Botcraft
{
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    const std::array<std::string, SalmonEntity::metadata_count> SalmonEntity::metadata_names{ {
        "data_type",
    } };
#endif

    SalmonEntity::SalmonEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SetDataType("medium");
#endif
    }

    SalmonEntity::~SalmonEntity()
    {

    }


    std::string SalmonEntity::GetName() const
    {
        return "salmon";
    }

    EntityType SalmonEntity::GetType() const
    {
        return EntityType::Salmon;
    }


    std::string SalmonEntity::GetClassName()
    {
        return "salmon";
    }

    EntityType SalmonEntity::GetClassType()
    {
        return EntityType::Salmon;
    }


#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    ProtocolCraft::Json::Value SalmonEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractSchoolingFishEntity::Serialize();

        output["metadata"]["data_type"] = GetDataType();

        return output;
    }


    void SalmonEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractSchoolingFishEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const std::string& SalmonEntity::GetDataType() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetDataTypeImpl();
    }

    const std::string& SalmonEntity::GetDataTypeImpl() const
    {
        return std::any_cast<const std::string&>(metadata.at("data_type"));
    }

    double SalmonEntity::GetScaleImpl() const
    {
        const std::string& type = GetDataTypeImpl();
        if (type == "medium")
        {
            return 1.0;
        }
        else if (type == "small")
        {
            return 0.5;
        }
        else
        {
            return 1.5;
        }
    }


    void SalmonEntity::SetDataType(const std::string& data_type)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_type"] = data_type;
#if USE_GUI
        OnSizeUpdated();
#endif
    }
#endif

    double SalmonEntity::GetWidthImpl() const
    {
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        return 0.7;
#else
        return 0.7 * GetScaleImpl();
#endif
    }

    double SalmonEntity::GetHeightImpl() const
    {
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        return 0.4;
#else
        return 0.4 * GetScaleImpl();
#endif
    }

}
#endif
