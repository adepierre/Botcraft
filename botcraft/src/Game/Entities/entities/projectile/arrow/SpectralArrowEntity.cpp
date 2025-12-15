#include "botcraft/Game/Entities/entities/projectile/arrow/SpectralArrowEntity.hpp"

namespace Botcraft
{
    SpectralArrowEntity::SpectralArrowEntity()
    {

    }

    SpectralArrowEntity::~SpectralArrowEntity()
    {

    }


    std::string SpectralArrowEntity::GetName() const
    {
        return "spectral_arrow";
    }

    EntityType SpectralArrowEntity::GetType() const
    {
        return EntityType::SpectralArrow;
    }


    std::string SpectralArrowEntity::GetClassName()
    {
        return "spectral_arrow";
    }

    EntityType SpectralArrowEntity::GetClassType()
    {
        return EntityType::SpectralArrow;
    }


    double SpectralArrowEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double SpectralArrowEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
