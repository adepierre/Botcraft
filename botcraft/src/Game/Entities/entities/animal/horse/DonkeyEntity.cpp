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
        return "Donkey";
    }

    EntityType DonkeyEntity::GetType() const
    {
        return EntityType::Donkey;
    }

    AABB DonkeyEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double DonkeyEntity::GetWidth() const
    {
        return 1.3964844;
    }

    double DonkeyEntity::GetHeight() const
    {
#if PROTOCOL_VERSION > 404
        return 1.5;
#else
        return 1.6;
#endif
    }


    std::string DonkeyEntity::GetClassName()
    {
        return "Donkey";
    }

    EntityType DonkeyEntity::GetClassType()
    {
        return EntityType::Donkey;
    }

}
