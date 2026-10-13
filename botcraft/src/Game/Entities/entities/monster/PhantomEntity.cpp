#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/monster/PhantomEntity.hpp"

namespace Botcraft
{
    PhantomEntity::PhantomEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    int PhantomEntity::GetIdSize() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("id_size"));
    }


    void PhantomEntity::SetIdSize(const int id_size)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("id_size"), id_size);
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
