#include "botcraft/Game/Entities/entities/UnknownEntity.hpp"

namespace Botcraft
{
    UnknownEntity::UnknownEntity()
    {

    }

    UnknownEntity::~UnknownEntity()
    {

    }

    std::string UnknownEntity::GetName() const
    {
        return "";
    }

    EntityType UnknownEntity::GetType() const
    {
        return EntityType::None;
    }

    double UnknownEntity::GetWidth() const
    {
        return 1.0;
    }

    double UnknownEntity::GetHeight() const
    {
        return 1.0;
    }
}
