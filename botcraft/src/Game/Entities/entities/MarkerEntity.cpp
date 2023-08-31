#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
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

    double MarkerEntity::GetWidth() const
    {
        return 0.0;
    }

    double MarkerEntity::GetHeight() const
    {
        return 0.0;
    }


    std::string MarkerEntity::GetClassName()
    {
        return "marker";
    }

    EntityType MarkerEntity::GetClassType()
    {
        return EntityType::Marker;
    }

}
#endif
