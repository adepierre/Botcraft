#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
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
        return "tadpole";
    }

    EntityType TadpoleEntity::GetType() const
    {
        return EntityType::Tadpole;
    }


    std::string TadpoleEntity::GetClassName()
    {
        return "tadpole";
    }

    EntityType TadpoleEntity::GetClassType()
    {
        return EntityType::Tadpole;
    }


    double TadpoleEntity::GetWidthImpl() const
    {
        return 0.4;
    }

    double TadpoleEntity::GetHeightImpl() const
    {
        return 0.3;
    }

}
#endif
