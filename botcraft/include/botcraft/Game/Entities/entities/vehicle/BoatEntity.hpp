#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class BoatEntity : public Entity
    {
    protected:
#if PROTOCOL_VERSION > 340
        static constexpr int metadata_count = 7;
#else
        static constexpr int metadata_count = 6;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        BoatEntity();
        virtual ~BoatEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataIdHurt() const;
        int GetDataIdHurtdir() const;
        float GetDataIdDamage() const;
        int GetDataIdType() const;
        bool GetDataIdPaddleLeft() const;
        bool GetDataIdPaddleRight() const;
#if PROTOCOL_VERSION > 340
        int GetDataIdBubbleTime() const;
#endif

        void SetDataIdHurt(const int data_id_hurt);
        void SetDataIdHurtdir(const int data_id_hurtdir);
        void SetDataIdDamage(const float data_id_damage);
        void SetDataIdType(const int data_id_type);
        void SetDataIdPaddleLeft(const bool data_id_paddle_left);
        void SetDataIdPaddleRight(const bool data_id_paddle_right);
#if PROTOCOL_VERSION > 340
        void SetDataIdBubbleTime(const int data_id_bubble_time);
#endif

    };
}
