#pragma once

#include "botcraft/Game/Entities/entities/projectile/hurtingprojectile/AbstractHurtingProjectileEntity.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Types/Item/Slot.hpp"
#endif

namespace Botcraft
{
    class FireballEntity : public AbstractHurtingProjectileEntity
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_item_stack"),
        };
#endif
    protected:
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
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
        ProtocolCraft::Slot GetDataItemStack() const;

        void SetDataItemStack(const ProtocolCraft::Slot& data_item_stack);
#endif

    };
}
