#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#include "botcraft/Game/Entities/entities/monster/skeleton/ParchedEntity.hpp"

namespace Botcraft
{
    ParchedEntity::ParchedEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 16.0) });
    }

    ParchedEntity::~ParchedEntity()
    {

    }


    std::string ParchedEntity::GetName() const
    {
        return "parched";
    }

    EntityType ParchedEntity::GetType() const
    {
        return EntityType::Parched;
    }


    std::string ParchedEntity::GetClassName()
    {
        return "parched";
    }

    EntityType ParchedEntity::GetClassType()
    {
        return EntityType::Parched;
    }


    double ParchedEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double ParchedEntity::GetHeightImpl() const
    {
        return 1.99;
    }

}
#endif
