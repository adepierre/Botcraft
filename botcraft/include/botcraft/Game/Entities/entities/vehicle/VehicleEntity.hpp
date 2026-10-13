#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class VehicleEntity : public Entity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_id_hurt"),
            std::string_view("data_id_hurtdir"),
            std::string_view("data_id_damage"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        VehicleEntity();
        virtual ~VehicleEntity();

        virtual bool IsVehicle() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataIdHurt() const;
        int GetDataIdHurtdir() const;
        float GetDataIdDamage() const;

        void SetDataIdHurt(const int data_id_hurt);
        void SetDataIdHurtdir(const int data_id_hurtdir);
        void SetDataIdDamage(const float data_id_damage);

    };
}
#endif
