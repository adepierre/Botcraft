#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
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
        return "phantom";
    }

    EntityType PhantomEntity::GetType() const
    {
        return EntityType::Phantom;
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
        return "phantom";
    }

    EntityType PhantomEntity::GetClassType()
    {
        return EntityType::Phantom;
    }


    ProtocolCraft::Json::Value PhantomEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = FlyingMobEntity::Serialize();

        output["metadata"]["id_size"] = GetIdSize();

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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int PhantomEntity::GetIdSize() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("id_size"));
    }


    void PhantomEntity::SetIdSize(const int id_size)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["id_size"] = id_size;
    }

}
#endif
