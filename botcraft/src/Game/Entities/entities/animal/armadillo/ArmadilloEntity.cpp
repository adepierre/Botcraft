#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/Entities/entities/animal/armadillo/ArmadilloEntity.hpp"

namespace Botcraft
{
    ArmadilloEntity::ArmadilloEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetArmadilloState(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 12.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.14) });
    }

    ArmadilloEntity::~ArmadilloEntity()
    {

    }


    std::string ArmadilloEntity::GetName() const
    {
        return "armadillo";
    }

    EntityType ArmadilloEntity::GetType() const
    {
        return EntityType::Armadillo;
    }


    std::string ArmadilloEntity::GetClassName()
    {
        return "armadillo";
    }

    EntityType ArmadilloEntity::GetClassType()
    {
        return EntityType::Armadillo;
    }


    ProtocolCraft::Json::Value ArmadilloEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["armadillo_state"] = GetArmadilloState();

        return output;
    }


    int ArmadilloEntity::GetArmadilloState() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("armadillo_state"));
    }


    void ArmadilloEntity::SetArmadilloState(const int armadillo_state)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("armadillo_state"), armadillo_state);
    }


    double ArmadilloEntity::GetWidthImpl() const
    {
        return 0.7;
    }

    double ArmadilloEntity::GetHeightImpl() const
    {
        return 0.65;
    }

}
#endif
