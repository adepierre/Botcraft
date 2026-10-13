#include "botcraft/Game/Entities/entities/vehicle/minecart/MinecartCommandBlockEntity.hpp"

namespace Botcraft
{
    MinecartCommandBlockEntity::MinecartCommandBlockEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataIdCommandName("");
        SetDataIdLastOutput(ProtocolCraft::Chat());
    }

    MinecartCommandBlockEntity::~MinecartCommandBlockEntity()
    {

    }


    std::string MinecartCommandBlockEntity::GetName() const
    {
        return "command_block_minecart";
    }

    EntityType MinecartCommandBlockEntity::GetType() const
    {
        return EntityType::MinecartCommandBlock;
    }


    std::string MinecartCommandBlockEntity::GetClassName()
    {
        return "command_block_minecart";
    }

    EntityType MinecartCommandBlockEntity::GetClassType()
    {
        return EntityType::MinecartCommandBlock;
    }


    ProtocolCraft::Json::Value MinecartCommandBlockEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractMinecartEntity::Serialize();

        output["metadata"]["data_id_command_name"] = GetDataIdCommandName();
        output["metadata"]["data_id_last_output"] = GetDataIdLastOutput().Serialize();

        return output;
    }


    std::string MinecartCommandBlockEntity::GetDataIdCommandName() const
    {
        return GetMetadata<std::string>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_command_name"));
    }

    ProtocolCraft::Chat MinecartCommandBlockEntity::GetDataIdLastOutput() const
    {
        return GetMetadata<ProtocolCraft::Chat>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_last_output"));
    }


    void MinecartCommandBlockEntity::SetDataIdCommandName(const std::string& data_id_command_name)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_command_name"), data_id_command_name);
    }

    void MinecartCommandBlockEntity::SetDataIdLastOutput(const ProtocolCraft::Chat& data_id_last_output)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_last_output"), data_id_last_output);
    }


    double MinecartCommandBlockEntity::GetWidthImpl() const
    {
        return 0.98;
    }

    double MinecartCommandBlockEntity::GetHeightImpl() const
    {
        return 0.7;
    }

}
