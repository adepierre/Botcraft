#include "botcraft/Game/Entities/entities/projectile/ThrownEnderpearlEntity.hpp"

namespace Botcraft
{
    ThrownEnderpearlEntity::ThrownEnderpearlEntity()
    {

    }

    ThrownEnderpearlEntity::~ThrownEnderpearlEntity()
    {

    }


    std::string ThrownEnderpearlEntity::GetName() const
    {
        return "ThrownEnderpearl";
    }

    EntityType ThrownEnderpearlEntity::GetType() const
    {
        return EntityType::ThrownEnderpearl;
    }

    AABB ThrownEnderpearlEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double ThrownEnderpearlEntity::GetWidth() const
    {
        return 0.25;
    }

    double ThrownEnderpearlEntity::GetHeight() const
    {
        return 0.25;
    }


    std::string ThrownEnderpearlEntity::GetClassName()
    {
        return "ThrownEnderpearl";
    }

    EntityType ThrownEnderpearlEntity::GetClassType()
    {
        return EntityType::ThrownEnderpearl;
    }

}
