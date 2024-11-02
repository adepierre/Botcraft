#include "botcraft/Game/Entities/entities/animal/OcelotEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, OcelotEntity::metadata_count> OcelotEntity::metadata_names{ {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        "data_trusting",
#else
        "data_type_id",
#endif
    } };

    OcelotEntity::OcelotEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        SetDataTrusting(false);
#else
        SetDataTypeId(0);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 3.0) });
    }

    OcelotEntity::~OcelotEntity()
    {

    }


    std::string OcelotEntity::GetName() const
    {
        return "ocelot";
    }

    EntityType OcelotEntity::GetType() const
    {
        return EntityType::Ocelot;
    }


    std::string OcelotEntity::GetClassName()
    {
        return "ocelot";
    }

    EntityType OcelotEntity::GetClassType()
    {
        return EntityType::Ocelot;
    }


    ProtocolCraft::Json::Value OcelotEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        output["metadata"]["data_trusting"] = GetDataTrusting();
#else
        output["metadata"]["data_type_id"] = GetDataTypeId();
#endif

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


    void OcelotEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    bool OcelotEntity::GetDataTrusting() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_trusting"));
    }


    void OcelotEntity::SetDataTrusting(const bool data_trusting)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_trusting"] = data_trusting;
    }
#else
    int OcelotEntity::GetDataTypeId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_type_id"));
    }


    void OcelotEntity::SetDataTypeId(const int data_type_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_type_id"] = data_type_id;
    }
#endif


    double OcelotEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }


    double OcelotEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double OcelotEntity::GetHeightImpl() const
    {
        return 0.7;
    }

}
