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

    AABB MuleEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
