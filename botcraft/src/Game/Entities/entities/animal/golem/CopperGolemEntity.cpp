#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "botcraft/Game/Entities/entities/animal/golem/CopperGolemEntity.hpp"

namespace Botcraft
{
    CopperGolemEntity::CopperGolemEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    int CopperGolemEntity::GetCopperGolemState() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("copper_golem_state"));
    }


    void CopperGolemEntity::SetCopperGolemState(const int copper_golem_state)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("copper_golem_state"), copper_golem_state);
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
