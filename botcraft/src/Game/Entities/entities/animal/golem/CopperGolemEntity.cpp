#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "botcraft/Game/Entities/entities/animal/golem/CopperGolemEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, CopperGolemEntity::metadata_count> CopperGolemEntity::metadata_names{ {
        "copper_golem_state",
    } };

    CopperGolemEntity::CopperGolemEntity()
    {
        // Initialize all metadata with default values
        SetCopperGolemState(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 12.0) });
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 1.0) });
    }

    CopperGolemEntity::~CopperGolemEntity()
    {

    }


    std::string CopperGolemEntity::GetName() const
    {
        return "copper_golem";
    }

    EntityType CopperGolemEntity::GetType() const
    {
        return EntityType::CopperGolem;
    }


    std::string CopperGolemEntity::GetClassName()
    {
        return "copper_golem";
    }

    EntityType CopperGolemEntity::GetClassType()
    {
        return EntityType::CopperGolem;
    }


    ProtocolCraft::Json::Value CopperGolemEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractGolemEntity::Serialize();

        output["metadata"]["copper_golem_state"] = GetCopperGolemState();

        return output;
    }


    void CopperGolemEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractGolemEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int CopperGolemEntity::GetCopperGolemState() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("copper_golem_state"));
    }


    void CopperGolemEntity::SetCopperGolemState(const int copper_golem_state)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["copper_golem_state"] = copper_golem_state;
    }


    double CopperGolemEntity::GetWidthImpl() const
    {
        return 0.49;
    }

    double CopperGolemEntity::GetHeightImpl() const
    {
        return 0.98;
    }

}
#endif
