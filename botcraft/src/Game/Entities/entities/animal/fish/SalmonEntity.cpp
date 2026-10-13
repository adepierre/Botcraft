#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/animal/fish/SalmonEntity.hpp"

namespace Botcraft
{
    SalmonEntity::SalmonEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
        SetDataType("medium");
#else
        SetDataType(1);
#endif
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


    void SalmonEntity::OnMetadataChangedImpl(const int index)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractSchoolingFishEntity::OnMetadataChangedImpl(index);
        }
#if USE_GUI
        else if (index == BOTCRAFT_ENTITY_METADATA_INDEX("data_type"))
        {
            OnSizeUpdated();
        }
#endif
    }

#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
    std::string SalmonEntity::GetDataType() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetDataTypeImpl();
    }

    const std::string& SalmonEntity::GetDataTypeImpl() const
    {
        return GetMetadataImpl<const std::string&>(BOTCRAFT_ENTITY_METADATA_INDEX("data_type"));
    }
#else
    int SalmonEntity::GetDataType() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetDataTypeImpl();
    }

    int SalmonEntity::GetDataTypeImpl() const
    {
        return GetMetadataImpl<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_type"));
    }
#endif

    double SalmonEntity::GetScaleImpl() const
    {
#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
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
#else
        switch (GetDataTypeImpl())
        {
        case 0:
            return 0.5;
        case 1:
            return 1.0;
        case 2:
            return 1.5;
        default:
            return 1.0;
        }
#endif
    }

#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
    void SalmonEntity::SetDataType(const std::string& data_type)
#else
    void SalmonEntity::SetDataType(const int data_type)
#endif
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_type"), data_type);
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
