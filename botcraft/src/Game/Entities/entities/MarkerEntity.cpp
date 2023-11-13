#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "botcraft/Game/Entities/entities/MarkerEntity.hpp"

namespace Botcraft
{
    MarkerEntity::MarkerEntity()
    {

    }

    MarkerEntity::~MarkerEntity()
    {

    }


    std::string MarkerEntity::GetName() const
    {
        return "marker";
    }

    EntityType MarkerEntity::GetType() const
    {
        return EntityType::Marker;
    }


    std::string MarkerEntity::GetClassName()
    {
        return "marker";
    }

    EntityType MarkerEntity::GetClassType()
    {
        return EntityType::Marker;
    }


    double MarkerEntity::GetWidthImpl() const
    {
        return 0.0;
    }

    double MarkerEntity::GetHeightImpl() const
    {
        return 0.0;
    }

}
#endif
