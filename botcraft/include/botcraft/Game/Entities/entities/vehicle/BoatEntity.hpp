#pragma once

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "botcraft/Game/Entities/entities/Entity.hpp"
#elif PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include "botcraft/Game/Entities/entities/vehicle/VehicleEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/vehicle/AbstractBoatEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    class BoatEntity : public Entity
#elif PROTOCOL_VERSION < 768 /* < 1.21.2 */
    class BoatEntity : public VehicleEntity
#else
    class BoatEntity : public AbstractBoatEntity
#endif
    {
    protected:
#if PROTOCOL_VERSION < 341 /* < 1.13 */
        static constexpr int metadata_count = 6;
#elif PROTOCOL_VERSION < 765 /* < 1.20.3 */
        static constexpr int metadata_count = 7;
#elif PROTOCOL_VERSION < 768 /* < 1.21.2 */
        static constexpr int metadata_count = 4;
#else
        static constexpr int metadata_count = 0;
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        static const std::array<std::string, metadata_count> metadata_names;
#endif
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;
#elif PROTOCOL_VERSION < 768 /* < 1.21.2 */
        static constexpr int hierarchy_metadata_count = VehicleEntity::metadata_count + VehicleEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = AbstractBoatEntity::metadata_count + AbstractBoatEntity::hierarchy_metadata_count;
#endif

    public:
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        BoatEntity();
#else
        BoatEntity(const EntityType type);
#endif
        virtual ~BoatEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        static EntityType GetClassType();
#else
        virtual bool IsBoat() const override;
#endif


        virtual ProtocolCraft::Json::Value Serialize() const override;

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
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
#endif

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    protected:
        const EntityType type;
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
