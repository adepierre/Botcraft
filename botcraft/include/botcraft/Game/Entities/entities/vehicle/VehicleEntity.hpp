#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class VehicleEntity : public Entity
    {
    protected:
        static constexpr int metadata_count = 3;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        VehicleEntity();
        virtual ~VehicleEntity();

        virtual bool IsVehicle() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataIdHurt() const;
        int GetDataIdHurtdir() const;
        float GetDataIdDamage() const;

        void SetDataIdHurt(const int data_id_hurt);
        void SetDataIdHurtdir(const int data_id_hurtdir);
        void SetDataIdDamage(const float data_id_damage);

    };
}
#endif
