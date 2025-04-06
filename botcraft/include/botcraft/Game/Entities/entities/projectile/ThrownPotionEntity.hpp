#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
#pragma once

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/projectile/ThrowableItemProjectileEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/projectile/ThrowableProjectileEntity.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    class ThrownPotionEntity : public ThrowableItemProjectileEntity
#else
    class ThrownPotionEntity : public ThrowableProjectileEntity
#endif
    {
    protected:
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = ThrowableItemProjectileEntity::metadata_count + ThrowableItemProjectileEntity::hierarchy_metadata_count;
#else
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = ThrowableProjectileEntity::metadata_count + ThrowableProjectileEntity::hierarchy_metadata_count;
#endif
    public:
        ThrownPotionEntity();
        virtual ~ThrownPotionEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


#if PROTOCOL_VERSION < 579 /* < 1.16 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        ProtocolCraft::Slot GetDataItemStack() const;

        void SetDataItemStack(const ProtocolCraft::Slot& data_item_stack);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
