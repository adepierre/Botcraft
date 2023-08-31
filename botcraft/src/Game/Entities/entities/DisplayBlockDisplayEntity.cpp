#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "botcraft/Game/Entities/entities/DisplayBlockDisplayEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, DisplayBlockDisplayEntity::metadata_count> DisplayBlockDisplayEntity::metadata_names{ {
        "data_block_state_id",
    } };

    DisplayBlockDisplayEntity::DisplayBlockDisplayEntity()
    {
        // Initialize all metadata with default values
        SetDataBlockStateId(0);
    }

    DisplayBlockDisplayEntity::~DisplayBlockDisplayEntity()
    {

    }


    std::string DisplayBlockDisplayEntity::GetName() const
    {
        return "block_display";
    }

    EntityType DisplayBlockDisplayEntity::GetType() const
    {
        return EntityType::DisplayBlockDisplay;
    }

    double DisplayBlockDisplayEntity::GetWidth() const
    {
        return 0.0;
    }

    double DisplayBlockDisplayEntity::GetHeight() const
    {
        return 0.0;
    }


    std::string DisplayBlockDisplayEntity::GetClassName()
    {
        return "block_display";
    }

    EntityType DisplayBlockDisplayEntity::GetClassType()
    {
        return EntityType::DisplayBlockDisplay;
    }
    


    ProtocolCraft::Json::Value DisplayBlockDisplayEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = DisplayEntity::Serialize();
        
        output["metadata"]["data_block_state_id"] = GetDataBlockStateId();

        return output;
    }


    void DisplayBlockDisplayEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            DisplayEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    
    int DisplayBlockDisplayEntity::GetDataBlockStateId() const
    {
        return std::any_cast<int>(metadata.at("data_block_state_id"));
    }
    
    
    void DisplayBlockDisplayEntity::SetDataBlockStateId(const int data_block_state_id)
    {
        metadata["data_block_state_id"] = data_block_state_id;
    }
}
#endif
