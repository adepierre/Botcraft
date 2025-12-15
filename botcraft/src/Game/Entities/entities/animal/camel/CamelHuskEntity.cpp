#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#include "botcraft/Game/Entities/entities/animal/camel/CamelHuskEntity.hpp"

#include <mutex>

namespace Botcraft
{
    CamelHuskEntity::CamelHuskEntity()
    {

    }

    CamelHuskEntity::~CamelHuskEntity()
    {

    }


    std::string CamelHuskEntity::GetName() const
    {
        return "camel_husk";
    }

    EntityType CamelHuskEntity::GetType() const
    {
        return EntityType::CamelHusk;
    }


    std::string CamelHuskEntity::GetClassName()
    {
        return "camel_husk";
    }

    EntityType CamelHuskEntity::GetClassType()
    {
        return EntityType::CamelHusk;
    }


    double CamelHuskEntity::GetWidthImpl() const
    {
        return 1.7;
    }

    double CamelHuskEntity::GetHeightImpl() const
    {
        return 2.375;
    }

}
#endif
