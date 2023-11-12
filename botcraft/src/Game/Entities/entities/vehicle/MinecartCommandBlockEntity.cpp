#include "botcraft/Game/Entities/entities/vehicle/MinecartCommandBlockEntity.hpp"

#include <mutex>

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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    std::string MinecartCommandBlockEntity::GetDataIdCommandName() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<std::string>(metadata.at("data_id_command_name"));
    }

    ProtocolCraft::Chat MinecartCommandBlockEntity::GetDataIdLastOutput() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<ProtocolCraft::Chat>(metadata.at("data_id_last_output"));
    }


    void MinecartCommandBlockEntity::SetDataIdCommandName(const std::string& data_id_command_name)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_command_name"] = data_id_command_name;
    }

    void MinecartCommandBlockEntity::SetDataIdLastOutput(const ProtocolCraft::Chat& data_id_last_output)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_last_output"] = data_id_last_output;
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
