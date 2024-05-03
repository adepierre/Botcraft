#include "botcraft/Game/Entities/entities/monster/MagmaCubeEntity.hpp"

namespace Botcraft
{
    MagmaCubeEntity::MagmaCubeEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
    }

    MagmaCubeEntity::~MagmaCubeEntity()
    {

    }


    std::string MagmaCubeEntity::GetName() const
    {
        return "magma_cube";
    }

    EntityType MagmaCubeEntity::GetType() const
    {
        return EntityType::MagmaCube;
    }


    std::string MagmaCubeEntity::GetClassName()
    {
        return "magma_cube";
    }

    EntityType MagmaCubeEntity::GetClassType()
    {
        return EntityType::MagmaCube;
    }

}
