#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/monster/PhantomEntity.hpp"

#include <mutex>

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
#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
        ProtocolCraft::Json::Value output = FlyingMobEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = MobEntity::Serialize();
#endif

        output["metadata"]["id_size"] = GetIdSize();

        return output;
    }


    void PhantomEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
            FlyingMobEntity::SetMetadataValue(index, value);
#else
            MobEntity::SetMetadataValue(index, value);
#endif
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


    double PhantomEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double PhantomEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
#endif
