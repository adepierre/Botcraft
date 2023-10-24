#pragma once

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/projectile/ProjectileEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/Entity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    class AbstractArrowEntity : public ProjectileEntity
#else
    class AbstractArrowEntity : public Entity
#endif
    {
    protected:
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        static constexpr int metadata_count = 2;
#elif PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = 3;
#elif PROTOCOL_VERSION > 393 /* > 1.13 */
        static constexpr int metadata_count = 2;
#else
        static constexpr int metadata_count = 1;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        static constexpr int hierarchy_metadata_count = ProjectileEntity::metadata_count + ProjectileEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;
#endif

    public:
        AbstractArrowEntity();
        virtual ~AbstractArrowEntity();

        virtual bool IsAbstractArrow() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        char GetIdFlags() const;
#if PROTOCOL_VERSION < 579 /* < 1.16 */ && PROTOCOL_VERSION > 393 /* > 1.13 */
        std::optional<ProtocolCraft::UUID> GetDataOwneruuidId() const;
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        char GetPierceLevel() const;
#endif

        void SetIdFlags(const char id_flags);
#if PROTOCOL_VERSION < 579 /* < 1.16 */ && PROTOCOL_VERSION > 393 /* > 1.13 */
        void SetDataOwneruuidId(const std::optional<ProtocolCraft::UUID>& data_owneruuid_id);
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        void SetPierceLevel(const char pierce_level);
#endif

    };
}
