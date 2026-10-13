#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "botcraft/Game/Entities/entities/animal/sniffer/SnifferEntity.hpp"

namespace Botcraft
{
    SnifferEntity::SnifferEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataState(0);
        SetDataDropSeedAtTick(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.1) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 14.0) });
    }

    SnifferEntity::~SnifferEntity()
    {

    }


    std::string SnifferEntity::GetName() const
    {
        return "sniffer";
    }

    EntityType SnifferEntity::GetType() const
    {
        return EntityType::Sniffer;
    }


    std::string SnifferEntity::GetClassName()
    {
        return "sniffer";
    }

    EntityType SnifferEntity::GetClassType()
    {
        return EntityType::Sniffer;
    }



    ProtocolCraft::Json::Value SnifferEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_state"] = GetDataState();
        output["metadata"]["data_drop_seed_at_tick"] = GetDataDropSeedAtTick();

        return output;
    }


    int SnifferEntity::GetDataState() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_state"));
    }

    int SnifferEntity::GetDataDropSeedAtTick() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_drop_seed_at_tick"));
    }


    void SnifferEntity::SetDataState(const int data_state)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_state"), data_state);
    }

    void SnifferEntity::SetDataDropSeedAtTick(const int data_drop_seed_at_tick)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_drop_seed_at_tick"), data_drop_seed_at_tick);
    }


    double SnifferEntity::GetWidthImpl() const
    {
        return 1.9;
    }

    double SnifferEntity::GetHeightImpl() const
    {
        return 1.75;
    }

}
#endif
