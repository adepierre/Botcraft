#include "botcraft/Game/Entities/entities/monster/MagmaCubeEntity.hpp"

namespace Botcraft
{
    MagmaCubeEntity::MagmaCubeEntity()
    {

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


    double MagmaCubeEntity::GetWidthImpl() const
    {
        return 0.255 * 2.04 * GetIdSizeImpl();
    }

    double MagmaCubeEntity::GetHeightImpl() const
    {
        return 0.255 * 2.04 * GetIdSizeImpl();
    }

}
