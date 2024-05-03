#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/Entities/entities/animal/armadillo/ArmadilloEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, ArmadilloEntity::metadata_count> ArmadilloEntity::metadata_names{ {
        "armadillo_state",
    } };

    ArmadilloEntity::ArmadilloEntity()
    {
        // Initialize all metadata with default values
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


    void ArmadilloEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int ArmadilloEntity::GetArmadilloState() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("armadillo_state"));
    }


    void ArmadilloEntity::SetArmadilloState(const int armadillo_state)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["armadillo_state"] = armadillo_state;
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
