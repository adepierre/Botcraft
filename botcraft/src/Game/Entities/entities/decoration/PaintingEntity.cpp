#include "botcraft/Game/Entities/entities/decoration/PaintingEntity.hpp"

namespace Botcraft
{
    PaintingEntity::PaintingEntity()
    {

    }

    PaintingEntity::~PaintingEntity()
    {

    }


    std::string PaintingEntity::GetName() const
    {
        return "Painting";
    }

    EntityType PaintingEntity::GetType() const
    {
        return EntityType::Painting;
    }

    double PaintingEntity::GetWidth() const
    {
        return 0.5;
    }

    double PaintingEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string PaintingEntity::GetClassName()
    {
        return "Painting";
    }

    EntityType PaintingEntity::GetClassType()
    {
        return EntityType::Painting;
    }

}
