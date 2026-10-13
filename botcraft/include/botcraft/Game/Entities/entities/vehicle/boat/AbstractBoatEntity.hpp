#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "botcraft/Game/Entities/entities/vehicle/VehicleEntity.hpp"

namespace Botcraft
{
    class AbstractBoatEntity : public VehicleEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_id_paddle_left"),
            std::string_view("data_id_paddle_right"),
            std::string_view("data_id_bubble_time"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = VehicleEntity::metadata_count + VehicleEntity::hierarchy_metadata_count;

    public:
        AbstractBoatEntity();
        virtual ~AbstractBoatEntity();

        virtual bool IsAbstractBoat() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetDataIdPaddleLeft() const;
        bool GetDataIdPaddleRight() const;
        int GetDataIdBubbleTime() const;

        void SetDataIdPaddleLeft(const bool data_id_paddle_left);
        void SetDataIdPaddleRight(const bool data_id_paddle_right);
        void SetDataIdBubbleTime(const int data_id_bubble_time);

    };
}
#endif
