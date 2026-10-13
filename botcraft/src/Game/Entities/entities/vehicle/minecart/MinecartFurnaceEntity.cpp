#include "botcraft/Game/Entities/entities/vehicle/minecart/MinecartFurnaceEntity.hpp"

namespace Botcraft
{
    MinecartFurnaceEntity::MinecartFurnaceEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    bool MinecartFurnaceEntity::GetDataIdFuel() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_fuel"));
    }


    void MinecartFurnaceEntity::SetDataIdFuel(const bool data_id_fuel)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_fuel"), data_id_fuel);
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
