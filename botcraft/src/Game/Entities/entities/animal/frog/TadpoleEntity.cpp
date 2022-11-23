#if PROTOCOL_VERSION > 758
#include "botcraft/Game/Entities/entities/animal/frog/TadpoleEntity.hpp"

namespace Botcraft
{
    TadpoleEntity::TadpoleEntity()
    {

    }

    TadpoleEntity::~TadpoleEntity()
    {

    }


    std::string TadpoleEntity::GetName() const
    {
        return "Tadpole";
    }

    EntityType TadpoleEntity::GetType() const
    {
        return EntityType::Tadpole;
    }

    double TadpoleEntity::GetWidth() const
    {
        return 0.4;
    }

    double TadpoleEntity::GetHeight() const
    {
        return 0.3;
    }


    std::string TadpoleEntity::GetClassName()
    {
        return "Tadpole";
    }

    EntityType TadpoleEntity::GetClassType()
    {
        return EntityType::Tadpole;
    }

}
#endif
