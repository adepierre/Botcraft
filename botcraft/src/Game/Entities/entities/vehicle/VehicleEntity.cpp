#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "botcraft/Game/Entities/entities/vehicle/VehicleEntity.hpp"

namespace Botcraft
{
    VehicleEntity::VehicleEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    int VehicleEntity::GetDataIdHurt() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_hurt"));
    }

    int VehicleEntity::GetDataIdHurtdir() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_hurtdir"));
    }

    float VehicleEntity::GetDataIdDamage() const
    {
        return GetMetadata<float>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_damage"));
    }


    void VehicleEntity::SetDataIdHurt(const int data_id_hurt)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_hurt"), data_id_hurt);
    }

    void VehicleEntity::SetDataIdHurtdir(const int data_id_hurtdir)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_hurtdir"), data_id_hurtdir);
    }

    void VehicleEntity::SetDataIdDamage(const float data_id_damage)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_damage"), data_id_damage);
    }

}
#endif
