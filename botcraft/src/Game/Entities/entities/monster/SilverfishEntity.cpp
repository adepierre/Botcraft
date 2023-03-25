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
        return "silverfish";
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
        return "silverfish";
    }

    EntityType SilverfishEntity::GetClassType()
    {
        return EntityType::Silverfish;
    }

}
