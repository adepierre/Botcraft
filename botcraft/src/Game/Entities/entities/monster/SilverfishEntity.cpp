#include "botcraft/Game/Entities/entities/monster/SilverfishEntity.hpp"

namespace Botcraft
{
    SilverfishEntity::SilverfishEntity()
    {

    }

    SilverfishEntity::~SilverfishEntity()
    {

    }


    std::string SilverfishEntity::GetName() const
    {
        return "Silverfish";
    }

    EntityType SilverfishEntity::GetType() const
    {
        return EntityType::Silverfish;
    }

    double SilverfishEntity::GetWidth() const
    {
        return 0.4;
    }

    double SilverfishEntity::GetHeight() const
    {
        return 0.3;
    }


    std::string SilverfishEntity::GetClassName()
    {
        return "Silverfish";
    }

    EntityType SilverfishEntity::GetClassType()
    {
        return EntityType::Silverfish;
    }

}
