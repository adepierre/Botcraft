#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "botcraft/Game/Entities/entities/vehicle/VehicleEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, VehicleEntity::metadata_count> VehicleEntity::metadata_names{ {
        "data_id_hurt",
        "data_id_hurtdir",
        "data_id_damage",
    } };

    VehicleEntity::VehicleEntity()
    {
        // Initialize all metadata with default values
        SetDataIdHurt(0);
        SetDataIdHurtdir(1);
        SetDataIdDamage(0.0f);
    }

    VehicleEntity::~VehicleEntity()
    {

    }

    bool VehicleEntity::IsVehicle() const
    {
        return true;
    }


    ProtocolCraft::Json::Value VehicleEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_id_hurt"] = GetDataIdHurt();
        output["metadata"]["data_id_hurtdir"] = GetDataIdHurtdir();
        output["metadata"]["data_id_damage"] = GetDataIdDamage();

        return output;
    }


    void VehicleEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int VehicleEntity::GetDataIdHurt() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_hurt"));
    }

    int VehicleEntity::GetDataIdHurtdir() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_hurtdir"));
    }

    float VehicleEntity::GetDataIdDamage() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_id_damage"));
    }


    void VehicleEntity::SetDataIdHurt(const int data_id_hurt)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_hurt"] = data_id_hurt;
    }

    void VehicleEntity::SetDataIdHurtdir(const int data_id_hurtdir)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_hurtdir"] = data_id_hurtdir;
    }

    void VehicleEntity::SetDataIdDamage(const float data_id_damage)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_damage"] = data_id_damage;
    }

}
#endif
