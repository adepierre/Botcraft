#include "botcraft/Game/Entities/entities/animal/squid/SquidEntity.hpp"

namespace Botcraft
{
    SquidEntity::SquidEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
    }

    SquidEntity::~SquidEntity()
    {

    }


    std::string SquidEntity::GetName() const
    {
        return "squid";
    }

    EntityType SquidEntity::GetType() const
    {
        return EntityType::Squid;
    }


    std::string SquidEntity::GetClassName()
    {
        return "squid";
    }

    EntityType SquidEntity::GetClassType()
    {
        return EntityType::Squid;
    }


    double SquidEntity::GetWidthImpl() const
    {
        return 0.8;
    }

    double SquidEntity::GetHeightImpl() const
    {
        return 0.8;
    }

}
