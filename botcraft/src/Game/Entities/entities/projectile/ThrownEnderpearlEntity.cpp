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
        return "ender_pearl";
    }

    EntityType ThrownEnderpearlEntity::GetType() const
    {
        return EntityType::ThrownEnderpearl;
    }


    std::string ThrownEnderpearlEntity::GetClassName()
    {
        return "ender_pearl";
    }

    EntityType ThrownEnderpearlEntity::GetClassType()
    {
        return EntityType::ThrownEnderpearl;
    }


    double ThrownEnderpearlEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double ThrownEnderpearlEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
