#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#include "botcraft/Game/Entities/entities/animal/nautilus/NautilusEntity.hpp"

namespace Botcraft
{
    NautilusEntity::NautilusEntity()
    {

    }

    NautilusEntity::~NautilusEntity()
    {

    }


    std::string NautilusEntity::GetName() const
    {
        return "nautilus";
    }

    EntityType NautilusEntity::GetType() const
    {
        return EntityType::Nautilus;
    }


    std::string NautilusEntity::GetClassName()
    {
        return "nautilus";
    }

    EntityType NautilusEntity::GetClassType()
    {
        return EntityType::Nautilus;
    }


    double NautilusEntity::GetWidthImpl() const
    {
        return 0.875;
    }

    double NautilusEntity::GetHeightImpl() const
    {
        return 0.95;
    }

}
#endif
