#include "botcraft/Game/Entities/entities/ExperienceOrbEntity.hpp"

namespace Botcraft
{
    ExperienceOrbEntity::ExperienceOrbEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        SetDataValue(0);
#endif
    }

    ExperienceOrbEntity::~ExperienceOrbEntity()
    {

    }


    std::string ExperienceOrbEntity::GetName() const
    {
        return "experience_orb";
    }

    EntityType ExperienceOrbEntity::GetType() const
    {
        return EntityType::ExperienceOrb;
    }


    std::string ExperienceOrbEntity::GetClassName()
    {
        return "experience_orb";
    }

    EntityType ExperienceOrbEntity::GetClassType()
    {
        return EntityType::ExperienceOrb;
    }

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    ProtocolCraft::Json::Value ExperienceOrbEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_value"] = GetDataValue();

        return output;
    }



    int ExperienceOrbEntity::GetDataValue() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_value"));
    }


    void ExperienceOrbEntity::SetDataValue(const int data_value)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_value"), data_value);
    }
#endif


    double ExperienceOrbEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double ExperienceOrbEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
