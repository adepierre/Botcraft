#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "botcraft/Game/Entities/entities/DisplayBlockDisplayEntity.hpp"

namespace Botcraft
{
    DisplayBlockDisplayEntity::DisplayBlockDisplayEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    int DisplayBlockDisplayEntity::GetDataBlockStateId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_block_state_id"));
    }


    void DisplayBlockDisplayEntity::SetDataBlockStateId(const int data_block_state_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_block_state_id"), data_block_state_id);
    }

    double DisplayBlockDisplayEntity::GetWidthImpl() const
    {
        return 0.0;
    }

    double DisplayBlockDisplayEntity::GetHeightImpl() const
    {
        return 0.0;
    }

}
#endif
