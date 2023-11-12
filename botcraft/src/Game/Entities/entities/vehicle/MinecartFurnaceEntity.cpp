#include "botcraft/Game/Entities/entities/vehicle/MinecartFurnaceEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, MinecartFurnaceEntity::metadata_count> MinecartFurnaceEntity::metadata_names{ {
        "data_id_fuel",
    } };

    MinecartFurnaceEntity::MinecartFurnaceEntity()
    {
        // Initialize all metadata with default values
        SetDataIdFuel(false);
    }

    MinecartFurnaceEntity::~MinecartFurnaceEntity()
    {

    }


    std::string MinecartFurnaceEntity::GetName() const
    {
        return "furnace_minecart";
    }

    EntityType MinecartFurnaceEntity::GetType() const
    {
        return EntityType::MinecartFurnace;
    }


    std::string MinecartFurnaceEntity::GetClassName()
    {
        return "furnace_minecart";
    }

    EntityType MinecartFurnaceEntity::GetClassType()
    {
        return EntityType::MinecartFurnace;
    }


    ProtocolCraft::Json::Value MinecartFurnaceEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractMinecartEntity::Serialize();

        output["metadata"]["data_id_fuel"] = GetDataIdFuel();

        return output;
    }


    void MinecartFurnaceEntity::SetMetadataValue(const int index, const std::any& value)
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

    bool MinecartFurnaceEntity::GetDataIdFuel() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_id_fuel"));
    }


    void MinecartFurnaceEntity::SetDataIdFuel(const bool data_id_fuel)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_fuel"] = data_id_fuel;
    }


    double MinecartFurnaceEntity::GetWidthImpl() const
    {
        return 0.98;
    }

    double MinecartFurnaceEntity::GetHeightImpl() const
    {
        return 0.7;
    }

}
