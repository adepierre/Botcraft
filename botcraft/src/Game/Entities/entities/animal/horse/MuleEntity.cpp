#include "botcraft/Game/Entities/entities/animal/horse/MuleEntity.hpp"

namespace Botcraft
{
    MuleEntity::MuleEntity()
    {

    }

    MuleEntity::~MuleEntity()
    {

    }


    std::string MuleEntity::GetName() const
    {
        return "Mule";
    }

    EntityType MuleEntity::GetType() const
    {
        return EntityType::Mule;
    }

    double MuleEntity::GetWidth() const
    {
        return 1.3964844;
    }

    double MuleEntity::GetHeight() const
    {
        return 1.6;
    }


    std::string MuleEntity::GetClassName()
    {
        return "Mule";
    }

    EntityType MuleEntity::GetClassType()
    {
        return EntityType::Mule;
    }

}
