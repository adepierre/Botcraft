#include "botcraft/Game/Entities/entities/vehicle/MinecartFurnaceEntity.hpp"

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
        return "MinecartFurnace";
    }

    EntityType MinecartFurnaceEntity::GetType() const
    {
        return EntityType::MinecartFurnace;
    }

    AABB MinecartFurnaceEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double MinecartFurnaceEntity::GetWidth() const
    {
        return 0.98;
    }

    double MinecartFurnaceEntity::GetHeight() const
    {
        return 0.7;
    }


    std::string MinecartFurnaceEntity::GetClassName()
    {
        return "MinecartFurnace";
    }

    EntityType MinecartFurnaceEntity::GetClassType()
    {
        return EntityType::MinecartFurnace;
    }


    nlohmann::json MinecartFurnaceEntity::Serialize() const
    {
        nlohmann::json output = AbstractMinecartEntity::Serialize();

        output["data_id_fuel"] = GetDataIdFuel();

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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool MinecartFurnaceEntity::GetDataIdFuel() const
    {
        return std::any_cast<bool>(metadata.at("data_id_fuel"));
    }


    void MinecartFurnaceEntity::SetDataIdFuel(const bool data_id_fuel)
    {
        metadata["data_id_fuel"] = data_id_fuel;
    }

}
