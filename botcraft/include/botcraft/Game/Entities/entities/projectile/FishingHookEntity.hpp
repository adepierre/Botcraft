#pragma once

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/projectile/ProjectileEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/Entity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    class FishingHookEntity : public ProjectileEntity
#else
    class FishingHookEntity : public Entity
#endif
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_hooked_entity"),
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
            std::string_view("data_biting"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        static constexpr int hierarchy_metadata_count = ProjectileEntity::metadata_count + ProjectileEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;
#endif

    public:
        FishingHookEntity();
        virtual ~FishingHookEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataHookedEntity() const;
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        bool GetDataBiting() const;
#endif

        void SetDataHookedEntity(const int data_hooked_entity);
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        void SetDataBiting(const bool data_biting);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
