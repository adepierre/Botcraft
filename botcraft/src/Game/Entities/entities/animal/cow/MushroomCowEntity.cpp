#include "botcraft/Game/Entities/entities/animal/cow/MushroomCowEntity.hpp"

namespace Botcraft
{
    MushroomCowEntity::MushroomCowEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
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


#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    std::string MushroomCowEntity::GetDataType() const
    {
        return GetMetadata<std::string>(BOTCRAFT_ENTITY_METADATA_INDEX("data_type"));
    }


    void MushroomCowEntity::SetDataType(const std::string& data_type)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_type"), data_type);
    }
#else
    int MushroomCowEntity::GetDataType() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_type"));
    }


    void MushroomCowEntity::SetDataType(const int data_type)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_type"), data_type);
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
