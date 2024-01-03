#pragma once

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "botcraft/Game/Entities/entities/Entity.hpp"
#else
#include "botcraft/Game/Entities/entities/vehicle/VehicleEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    class BoatEntity : public Entity
#else
    class BoatEntity : public VehicleEntity
#endif
    {
    protected:
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        static constexpr int metadata_count = 7;
#else
        static constexpr int metadata_count = 4;
#endif
#else
        static constexpr int metadata_count = 6;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = VehicleEntity::metadata_count + VehicleEntity::hierarchy_metadata_count;
#endif

    public:
        BoatEntity();
        virtual ~BoatEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        int GetDataIdHurt() const;
        int GetDataIdHurtdir() const;
        float GetDataIdDamage() const;
#endif
        int GetDataIdType() const;
        bool GetDataIdPaddleLeft() const;
        bool GetDataIdPaddleRight() const;
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        int GetDataIdBubbleTime() const;
#endif

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        void SetDataIdHurt(const int data_id_hurt);
        void SetDataIdHurtdir(const int data_id_hurtdir);
        void SetDataIdDamage(const float data_id_damage);
#endif
        void SetDataIdType(const int data_id_type);
        void SetDataIdPaddleLeft(const bool data_id_paddle_left);
        void SetDataIdPaddleRight(const bool data_id_paddle_right);
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        void SetDataIdBubbleTime(const int data_id_bubble_time);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
