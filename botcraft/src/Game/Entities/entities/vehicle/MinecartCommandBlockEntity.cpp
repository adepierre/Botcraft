#include "botcraft/Game/Entities/entities/vehicle/MinecartCommandBlockEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, MinecartCommandBlockEntity::metadata_count> MinecartCommandBlockEntity::metadata_names{ {
        "data_id_command_name",
        "data_id_last_output",
    } };

    MinecartCommandBlockEntity::MinecartCommandBlockEntity()
    {
        // Initialize all metadata with default values
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

    double MinecartCommandBlockEntity::GetWidth() const
    {
        return 0.98;
    }

    double MinecartCommandBlockEntity::GetHeight() const
    {
        return 0.7;
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


    void MinecartCommandBlockEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractMinecartEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const std::string& MinecartCommandBlockEntity::GetDataIdCommandName() const
    {
        return std::any_cast<const std::string&>(metadata.at("data_id_command_name"));
    }

    const ProtocolCraft::Chat& MinecartCommandBlockEntity::GetDataIdLastOutput() const
    {
        return std::any_cast<const ProtocolCraft::Chat&>(metadata.at("data_id_last_output"));
    }


    void MinecartCommandBlockEntity::SetDataIdCommandName(const std::string& data_id_command_name)
    {
        metadata["data_id_command_name"] = data_id_command_name;
    }

    void MinecartCommandBlockEntity::SetDataIdLastOutput(const ProtocolCraft::Chat& data_id_last_output)
    {
        metadata["data_id_last_output"] = data_id_last_output;
    }

}
