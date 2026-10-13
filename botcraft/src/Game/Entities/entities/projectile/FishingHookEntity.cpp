#include "botcraft/Game/Entities/entities/projectile/FishingHookEntity.hpp"

namespace Botcraft
{
    FishingHookEntity::FishingHookEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataHookedEntity(0);
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        SetDataBiting(false);
#endif
    }

    FishingHookEntity::~FishingHookEntity()
    {

    }


    std::string FishingHookEntity::GetName() const
    {
        return "fishing_bobber";
    }

    EntityType FishingHookEntity::GetType() const
    {
        return EntityType::FishingHook;
    }


    std::string FishingHookEntity::GetClassName()
    {
        return "fishing_bobber";
    }

    EntityType FishingHookEntity::GetClassType()
    {
        return EntityType::FishingHook;
    }

    ProtocolCraft::Json::Value FishingHookEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        ProtocolCraft::Json::Value output = ProjectileEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = Entity::Serialize();
#endif

        output["metadata"]["data_hooked_entity"] = GetDataHookedEntity();
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        output["metadata"]["data_biting"] = GetDataBiting();
#endif

        return output;
    }


    int FishingHookEntity::GetDataHookedEntity() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_hooked_entity"));
    }

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    bool FishingHookEntity::GetDataBiting() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_biting"));
    }
#endif


    void FishingHookEntity::SetDataHookedEntity(const int data_hooked_entity)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_hooked_entity"), data_hooked_entity);
    }

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    void FishingHookEntity::SetDataBiting(const bool data_biting)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_biting"), data_biting);
    }
#endif


    double FishingHookEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double FishingHookEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
