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

    AABB PaintingEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
