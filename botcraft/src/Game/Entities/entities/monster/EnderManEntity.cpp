#include "botcraft/Game/Entities/entities/monster/EnderManEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, EnderManEntity::metadata_count> EnderManEntity::metadata_names{ {
        "data_carry_state",
        "data_creepy",
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        "data_stared_at",
#endif
    } };

    EnderManEntity::EnderManEntity()
    {
        // Initialize all metadata with default values
        SetDataCarryState(0);
        SetDataCreepy(false);
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        SetDataStaredAt(false);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 40.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 7.0) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 64.0) });
    }

    EnderManEntity::~EnderManEntity()
    {

    }


    std::string EnderManEntity::GetName() const
    {
        return "enderman";
    }

    EntityType EnderManEntity::GetType() const
    {
        return EntityType::EnderMan;
    }


    std::string EnderManEntity::GetClassName()
    {
        return "enderman";
    }

    EntityType EnderManEntity::GetClassType()
    {
        return EntityType::EnderMan;
    }


    ProtocolCraft::Json::Value EnderManEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_carry_state"] = GetDataCarryState();
        output["metadata"]["data_creepy"] = GetDataCreepy();
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        output["metadata"]["data_stared_at"] = GetDataStaredAt();
#endif

        return output;
    }


    void EnderManEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int EnderManEntity::GetDataCarryState() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_carry_state"));
    }

    bool EnderManEntity::GetDataCreepy() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_creepy"));
    }

#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
    bool EnderManEntity::GetDataStaredAt() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_stared_at"));
    }
#endif


    void EnderManEntity::SetDataCarryState(const int data_carry_state)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_carry_state"] = data_carry_state;
    }

    void EnderManEntity::SetDataCreepy(const bool data_creepy)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_creepy"] = data_creepy;
    }

#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
    void EnderManEntity::SetDataStaredAt(const bool data_stared_at)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_stared_at"] = data_stared_at;
    }
#endif


    double EnderManEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double EnderManEntity::GetHeightImpl() const
    {
        return 2.9;
    }

}
