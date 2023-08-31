#pragma once

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/projectile/ProjectileEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/Entity.hpp"
#endif
#include "protocolCraft/Types/Slot.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    class FireworkRocketEntity : public ProjectileEntity
#else
    class FireworkRocketEntity : public Entity
#endif
    {
    protected:
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = 3;
#else
        static constexpr int metadata_count = 2;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        static constexpr int hierarchy_metadata_count = ProjectileEntity::metadata_count + ProjectileEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;
#endif

    public:
        FireworkRocketEntity();
        virtual ~FireworkRocketEntity();

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

        const ProtocolCraft::Slot& GetDataIdFireworksItem() const;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        const std::optional<int>& GetDataAttachedToTarget() const;
        bool GetDataShotAtAngle() const;
#else
        int GetDataAttachedToTarget() const;
#endif

        void SetDataIdFireworksItem(const ProtocolCraft::Slot& data_id_fireworks_item);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        void SetDataAttachedToTarget(const std::optional<int>& data_attached_to_target);
        void SetDataShotAtAngle(const bool data_shot_at_angle);
#else
        void SetDataAttachedToTarget(const int data_attached_to_target);
#endif

    };
}
