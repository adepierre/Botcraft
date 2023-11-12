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
        return "mule";
    }

    EntityType MuleEntity::GetType() const
    {
        return EntityType::Mule;
    }


    std::string MuleEntity::GetClassName()
    {
        return "mule";
    }

    EntityType MuleEntity::GetClassType()
    {
        return EntityType::Mule;
    }


    double MuleEntity::GetWidthImpl() const
    {
        return 1.3964844;
    }

    double MuleEntity::GetHeightImpl() const
    {
        return 1.6;
    }

}
