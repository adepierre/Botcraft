#include "botcraft/Game/Entities/entities/projectile/arrow/AbstractArrowEntity.hpp"

namespace Botcraft
{
    AbstractArrowEntity::AbstractArrowEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetIdFlags(0);
#if PROTOCOL_VERSION < 579 /* < 1.16 */ && PROTOCOL_VERSION > 393 /* > 1.13 */
        SetDataOwneruuidId(std::optional<ProtocolCraft::UUID>());
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        SetPierceLevel(0);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SetInGround(false);
#endif
    }

    AbstractArrowEntity::~AbstractArrowEntity()
    {

    }

    bool AbstractArrowEntity::IsAbstractArrow() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractArrowEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        ProtocolCraft::Json::Value output = ProjectileEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = Entity::Serialize();
#endif

        output["metadata"]["id_flags"] = GetIdFlags();
#if PROTOCOL_VERSION < 579 /* < 1.16 */ && PROTOCOL_VERSION > 393 /* > 1.13 */
        output["metadata"]["data_owneruuid_id"] = GetDataOwneruuidId() ? ProtocolCraft::Json::Value(GetDataOwneruuidId().value()) : ProtocolCraft::Json::Value();
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        output["metadata"]["pierce_level"] = GetPierceLevel();
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        output["metadata"]["in_ground"] = GetInGround();
#endif

        return output;
    }


    char AbstractArrowEntity::GetIdFlags() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("id_flags"));
    }

#if PROTOCOL_VERSION < 579 /* < 1.16 */ && PROTOCOL_VERSION > 393 /* > 1.13 */
    std::optional<ProtocolCraft::UUID> AbstractArrowEntity::GetDataOwneruuidId() const
    {
        return GetMetadata<std::optional<ProtocolCraft::UUID>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_owneruuid_id"));
    }
#endif

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    char AbstractArrowEntity::GetPierceLevel() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("pierce_level"));
    }
#endif

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    bool AbstractArrowEntity::GetInGround() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("in_ground"));
    }
#endif


    void AbstractArrowEntity::SetIdFlags(const char id_flags)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("id_flags"), id_flags);
    }

#if PROTOCOL_VERSION < 579 /* < 1.16 */ && PROTOCOL_VERSION > 393 /* > 1.13 */
    void AbstractArrowEntity::SetDataOwneruuidId(const std::optional<ProtocolCraft::UUID>& data_owneruuid_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_owneruuid_id"), data_owneruuid_id);
    }
#endif

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    void AbstractArrowEntity::SetPierceLevel(const char pierce_level)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("pierce_level"), pierce_level);
    }
#endif

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    void AbstractArrowEntity::SetInGround(const bool in_ground)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("in_ground"), in_ground);
    }
#endif

}
