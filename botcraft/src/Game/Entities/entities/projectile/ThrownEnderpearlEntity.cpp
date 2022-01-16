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
