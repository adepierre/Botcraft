#include "botcraft/Game/Entities/entities/projectile/FishingHookEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, FishingHookEntity::metadata_count> FishingHookEntity::metadata_names{ {
        "data_hooked_entity",
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        "data_biting",
#endif
    } };

    FishingHookEntity::FishingHookEntity()
    {
        // Initialize all metadata with default values
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

    double FishingHookEntity::GetWidth() const
    {
        return 0.25;
    }

    double FishingHookEntity::GetHeight() const
    {
        return 0.25;
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


    void FishingHookEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
            ProjectileEntity::SetMetadataValue(index, value);
#else
            Entity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int FishingHookEntity::GetDataHookedEntity() const
    {
        return std::any_cast<int>(metadata.at("data_hooked_entity"));
    }

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    bool FishingHookEntity::GetDataBiting() const
    {
        return std::any_cast<bool>(metadata.at("data_biting"));
    }
#endif


    void FishingHookEntity::SetDataHookedEntity(const int data_hooked_entity)
    {
        metadata["data_hooked_entity"] = data_hooked_entity;
    }

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    void FishingHookEntity::SetDataBiting(const bool data_biting)
    {
        metadata["data_biting"] = data_biting;
    }
#endif

}
