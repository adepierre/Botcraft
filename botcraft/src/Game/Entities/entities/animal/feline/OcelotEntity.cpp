#include "botcraft/Game/Entities/entities/animal/feline/OcelotEntity.hpp"

namespace Botcraft
{
    OcelotEntity::OcelotEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    bool OcelotEntity::GetDataTrusting() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_trusting"));
    }


    void OcelotEntity::SetDataTrusting(const bool data_trusting)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_trusting"), data_trusting);
    }
#else
    int OcelotEntity::GetDataTypeId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_type_id"));
    }


    void OcelotEntity::SetDataTypeId(const int data_type_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_type_id"), data_type_id);
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
