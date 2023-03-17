#if PROTOCOL_VERSION > 761
#include "botcraft/Game/Entities/entities/animal/sniffer/SnifferEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, SnifferEntity::metadata_count> SnifferEntity::metadata_names{ {
        "data_state",
        "data_drop_seed_at_tick",
    } };

    SnifferEntity::SnifferEntity()
    {
        // Initialize all metadata with default values
        SetDataState(0);
        SetDataDropSeedAtTick(0);
    }

    SnifferEntity::~SnifferEntity()
    {

    }


    std::string SnifferEntity::GetName() const
    {
        return "Sniffer";
    }

    EntityType SnifferEntity::GetType() const
    {
        return EntityType::Sniffer;
    }

    double SnifferEntity::GetWidth() const
    {
        return 1.9;
    }

    double SnifferEntity::GetHeight() const
    {
        return 1.75;
    }


    std::string SnifferEntity::GetClassName()
    {
        return "Sniffer";
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


    void SnifferEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    
    int SnifferEntity::GetDataState() const
    {
        return std::any_cast<int>(metadata.at("data_state"));
    }
    
    int SnifferEntity::GetDataDropSeedAtTick() const
    {
        return std::any_cast<int>(metadata.at("data_drop_seed_at_tick"));
    }
    
    
    void SnifferEntity::SetDataState(const int data_state)
    {
        metadata["data_state"] = data_state;
    }
    
    void SnifferEntity::SetDataDropSeedAtTick(const int data_drop_seed_at_tick)
    {
        metadata["data_drop_seed_at_tick"] = data_drop_seed_at_tick;
    }
    

}
#endif
