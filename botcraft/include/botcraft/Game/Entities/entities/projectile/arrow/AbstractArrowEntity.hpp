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
    private:
        static constexpr std::array metadata_names{
            std::string_view("id_flags"),
#if PROTOCOL_VERSION < 579 /* < 1.16 */ && PROTOCOL_VERSION > 393 /* > 1.13 */
            std::string_view("data_owneruuid_id"),
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
            std::string_view("pierce_level"),
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            std::string_view("in_ground"),
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
        AbstractArrowEntity();
        virtual ~AbstractArrowEntity();

        virtual bool IsAbstractArrow() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        char GetIdFlags() const;
#if PROTOCOL_VERSION < 579 /* < 1.16 */ && PROTOCOL_VERSION > 393 /* > 1.13 */
        std::optional<ProtocolCraft::UUID> GetDataOwneruuidId() const;
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        char GetPierceLevel() const;
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        bool GetInGround() const;
#endif

        void SetIdFlags(const char id_flags);
#if PROTOCOL_VERSION < 579 /* < 1.16 */ && PROTOCOL_VERSION > 393 /* > 1.13 */
        void SetDataOwneruuidId(const std::optional<ProtocolCraft::UUID>& data_owneruuid_id);
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        void SetPierceLevel(const char pierce_level);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        void SetInGround(const bool in_ground);
#endif

    };
}
