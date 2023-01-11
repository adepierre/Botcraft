#pragma once

#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/projectile/ProjectileEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/Entity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 578
    class FishingHookEntity : public ProjectileEntity
#else
    class FishingHookEntity : public Entity
#endif
    {
    protected:
#if PROTOCOL_VERSION > 578
        static constexpr int metadata_count = 2;
#else
        static constexpr int metadata_count = 1;
#endif
        static const std::array<std::string, metadata_count> metadata_names;

#if PROTOCOL_VERSION > 578
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
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataHookedEntity() const;
#if PROTOCOL_VERSION > 578
        bool GetDataBiting() const;
#endif

        void SetDataHookedEntity(const int data_hooked_entity);
#if PROTOCOL_VERSION > 578
        void SetDataBiting(const bool data_biting);
#endif

    };
}
