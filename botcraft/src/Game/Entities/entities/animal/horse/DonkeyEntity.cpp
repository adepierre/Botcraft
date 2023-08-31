#include "botcraft/Game/Entities/entities/animal/horse/DonkeyEntity.hpp"

namespace Botcraft
{
    DonkeyEntity::DonkeyEntity()
    {

    }

    DonkeyEntity::~DonkeyEntity()
    {

    }


    std::string DonkeyEntity::GetName() const
    {
        return "donkey";
    }

    EntityType DonkeyEntity::GetType() const
    {
        return EntityType::Donkey;
    }

    double DonkeyEntity::GetWidth() const
    {
        return 1.3964844;
    }

    double DonkeyEntity::GetHeight() const
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        return 1.5;
#else
        return 1.6;
#endif
    }


    std::string DonkeyEntity::GetClassName()
    {
        return "donkey";
    }

    EntityType DonkeyEntity::GetClassType()
    {
        return EntityType::Donkey;
    }

}
