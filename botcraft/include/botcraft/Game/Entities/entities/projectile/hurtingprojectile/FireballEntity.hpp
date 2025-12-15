#pragma once

#include "botcraft/Game/Entities/entities/projectile/hurtingprojectile/AbstractHurtingProjectileEntity.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Types/Item/Slot.hpp"
#endif

namespace Botcraft
{
    class FireballEntity : public AbstractHurtingProjectileEntity
    {
    protected:
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#else
        static constexpr int metadata_count = 0;
#endif
        static constexpr int hierarchy_metadata_count = AbstractHurtingProjectileEntity::metadata_count + AbstractHurtingProjectileEntity::hierarchy_metadata_count;

    public:
        FireballEntity();
        virtual ~FireballEntity();

        virtual bool IsFireball() const override;

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        ProtocolCraft::Slot GetDataItemStack() const;

        void SetDataItemStack(const ProtocolCraft::Slot& data_item_stack);
#endif

    };
}
