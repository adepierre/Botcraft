#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class AbstractMinecartEntity : public Entity
    {
    protected:
        static constexpr int metadata_count = 6;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        AbstractMinecartEntity();
        virtual ~AbstractMinecartEntity();

        virtual bool IsAbstractMinecart() const override;

        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataIdHurt() const;
        int GetDataIdHurtdir() const;
        float GetDataIdDamage() const;
        int GetDataIdDisplayBlock() const;
        int GetDataIdDisplayOffset() const;
        bool GetDataIdCustomDisplay() const;

        void SetDataIdHurt(const int data_id_hurt);
        void SetDataIdHurtdir(const int data_id_hurtdir);
        void SetDataIdDamage(const float data_id_damage);
        void SetDataIdDisplayBlock(const int data_id_display_block);
        void SetDataIdDisplayOffset(const int data_id_display_offset);
        void SetDataIdCustomDisplay(const bool data_id_custom_display);

    };
}
