#include "botcraft/Game/Entities/entities/ExperienceOrbEntity.hpp"

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include <mutex>
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    const std::array<std::string, ExperienceOrbEntity::metadata_count> ExperienceOrbEntity::metadata_names{ {
        "data_value",
    } };
#endif

    ExperienceOrbEntity::ExperienceOrbEntity()
    {
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        // Initialize all metadata with default values
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



    void ExperienceOrbEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int ExperienceOrbEntity::GetDataValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_value"));
    }


    void ExperienceOrbEntity::SetDataValue(const int data_value)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_value"] = data_value;
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
