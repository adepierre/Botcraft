#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "botcraft/Game/Entities/entities/vehicle/VehicleEntity.hpp"

namespace Botcraft
{
    class AbstractBoatEntity : public VehicleEntity
    {
    protected:
        static constexpr int metadata_count = 3;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = VehicleEntity::metadata_count + VehicleEntity::hierarchy_metadata_count;

    public:
        AbstractBoatEntity();
        virtual ~AbstractBoatEntity();

        virtual bool IsAbstractBoat() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDataIdPaddleLeft() const;
        bool GetDataIdPaddleRight() const;
        int GetDataIdBubbleTime() const;

        void SetDataIdPaddleLeft(const bool data_id_paddle_left);
        void SetDataIdPaddleRight(const bool data_id_paddle_right);
        void SetDataIdBubbleTime(const int data_id_bubble_time);

    };
}
#endif
