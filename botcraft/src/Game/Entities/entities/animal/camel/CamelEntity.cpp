#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "botcraft/Game/Entities/entities/animal/camel/CamelEntity.hpp"

namespace Botcraft
{
    CamelEntity::CamelEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDash(true);
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        SetLastPoseChangeTick(-52);
#else
        SetLastPoseChangeTick(0);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 32.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.09) });
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        attributes.insert({ EntityAttribute::Type::HorseJumpStrength, EntityAttribute(EntityAttribute::Type::HorseJumpStrength, 0.42) });
#else
        attributes.insert({ EntityAttribute::Type::JumpStrength, EntityAttribute(EntityAttribute::Type::JumpStrength, 0.42) });
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 1.5) });
#endif
    }

    CamelEntity::~CamelEntity()
    {

    }


    std::string CamelEntity::GetName() const
    {
        return "camel";
    }

    EntityType CamelEntity::GetType() const
    {
        return EntityType::Camel;
    }


    std::string CamelEntity::GetClassName()
    {
        return "camel";
    }

    EntityType CamelEntity::GetClassType()
    {
        return EntityType::Camel;
    }


    ProtocolCraft::Json::Value CamelEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractHorseEntity::Serialize();

        output["metadata"]["dash"] = GetDash();
        output["metadata"]["last_pose_change_tick"] = GetLastPoseChangeTick();

        return output;
    }


    bool CamelEntity::GetDash() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("dash"));
    }

    long long int CamelEntity::GetLastPoseChangeTick() const
    {
        return GetMetadata<long long int>(BOTCRAFT_ENTITY_METADATA_INDEX("last_pose_change_tick"));
    }


    void CamelEntity::SetDash(const bool dash)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("dash"), dash);
    }

    void CamelEntity::SetLastPoseChangeTick(const long long int last_pose_change_tick)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("last_pose_change_tick"), last_pose_change_tick);
    }


    double CamelEntity::GetWidthImpl() const
    {
        return 1.7;
    }

    double CamelEntity::GetHeightImpl() const
    {
        return 2.375;
    }

}
#endif
