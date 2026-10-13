#pragma once

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "botcraft/Game/Entities/entities/Entity.hpp"
#else
#include "botcraft/Game/Entities/entities/vehicle/VehicleEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    class AbstractMinecartEntity : public Entity
#else
    class AbstractMinecartEntity : public VehicleEntity
#endif
    {
    private:
        static constexpr std::array metadata_names{
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
            std::string_view("data_id_hurt"),
            std::string_view("data_id_hurtdir"),
            std::string_view("data_id_damage"),
#endif
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            std::string_view("data_id_display_block"),
#else
            std::string_view("data_id_custom_display_block"),
#endif
            std::string_view("data_id_display_offset"),
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            std::string_view("data_id_custom_display"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = VehicleEntity::metadata_count + VehicleEntity::hierarchy_metadata_count;
#endif

    public:
        AbstractMinecartEntity();
        virtual ~AbstractMinecartEntity();

        virtual bool IsAbstractMinecart() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        int GetDataIdHurt() const;
        int GetDataIdHurtdir() const;
        float GetDataIdDamage() const;
#endif
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        int GetDataIdDisplayBlock() const;
#else
        int GetDataIdCustomDisplayBlock() const;
#endif
        int GetDataIdDisplayOffset() const;
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        bool GetDataIdCustomDisplay() const;
#endif

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        void SetDataIdHurt(const int data_id_hurt);
        void SetDataIdHurtdir(const int data_id_hurtdir);
        void SetDataIdDamage(const float data_id_damage);
#endif
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        void SetDataIdDisplayBlock(const int data_id_display_block);
#else
        void SetDataIdCustomDisplayBlock(const int data_id_display_block);
#endif
        void SetDataIdDisplayOffset(const int data_id_display_offset);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        void SetDataIdCustomDisplay(const bool data_id_custom_display);
#endif

    };
}
