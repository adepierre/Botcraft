#pragma once

#include "botcraft/Game/Entities/entities/projectile/ThrowableProjectileEntity.hpp"
#if PROTOCOL_VERSION > 404
#include "protocolCraft/Types/Slot.hpp"
#endif

namespace Botcraft
{
    class ThrowableItemProjectileEntity : public ThrowableProjectileEntity
    {
    protected:
#if PROTOCOL_VERSION > 404
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#else
        static constexpr int metadata_count = 0;
#endif
        static constexpr int hierarchy_metadata_count = ThrowableProjectileEntity::metadata_count + ThrowableProjectileEntity::hierarchy_metadata_count;

    public:
        ThrowableItemProjectileEntity();
        virtual ~ThrowableItemProjectileEntity();

        virtual bool IsThrowableItemProjectile() const override;

#if PROTOCOL_VERSION > 404
        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        const ProtocolCraft::Slot& GetDataItemStack() const;

        void SetDataItemStack(const ProtocolCraft::Slot& data_item_stack);
#endif

    };
}
