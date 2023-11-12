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


    double UnknownEntity::GetWidthImpl() const
    {
        return 1.0;
    }

    double UnknownEntity::GetHeightImpl() const
    {
        return 1.0;
    }

}
