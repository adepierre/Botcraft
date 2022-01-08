#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/monster/PhantomEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, PhantomEntity::metadata_count> PhantomEntity::metadata_names{ {
        "id_size",
    } };

    PhantomEntity::PhantomEntity()
    {
        // Initialize all metadata with default values
        SetIdSize(0);
    }

    PhantomEntity::~PhantomEntity()
    {

    }


    std::string PhantomEntity::GetName() const
    {
        return "Phantom";
    }

    EntityType PhantomEntity::GetType() const
    {
        return EntityType::Phantom;
    }

    AABB PhantomEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double PhantomEntity::GetWidth() const
    {
        return 0.9;
    }

    double PhantomEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string PhantomEntity::GetClassName()
    {
        return "Phantom";
    }

    EntityType PhantomEntity::GetClassType()
    {
        return EntityType::Phantom;
    }


    nlohmann::json PhantomEntity::Serialize() const
    {
        nlohmann::json output = FlyingMobEntity::Serialize();

        output["id_size"] = GetIdSize();

        return output;
    }


    void PhantomEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            FlyingMobEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int PhantomEntity::GetIdSize() const
    {
        return std::any_cast<int>(metadata.at("id_size"));
    }


    void PhantomEntity::SetIdSize(const int id_size)
    {
        metadata["id_size"] = id_size;
    }

}
#endif
