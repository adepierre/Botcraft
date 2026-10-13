#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "botcraft/Game/Entities/entities/animal/axolotl/AxolotlEntity.hpp"

namespace Botcraft
{
    AxolotlEntity::AxolotlEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataVariant(0);
        SetDataPlayingDead(false);
        SetFromBucket(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 14.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 1.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 2.0) });
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 1.0) });
#endif

    }

    AxolotlEntity::~AxolotlEntity()
    {

    }


    std::string AxolotlEntity::GetName() const
    {
        return "axolotl";
    }

    EntityType AxolotlEntity::GetType() const
    {
        return EntityType::Axolotl;
    }


    std::string AxolotlEntity::GetClassName()
    {
        return "axolotl";
    }

    EntityType AxolotlEntity::GetClassType()
    {
        return EntityType::Axolotl;
    }


    ProtocolCraft::Json::Value AxolotlEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_variant"] = GetDataVariant();
        output["metadata"]["data_playing_dead"] = GetDataPlayingDead();
        output["metadata"]["from_bucket"] = GetFromBucket();

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();


        return output;
    }


    int AxolotlEntity::GetDataVariant() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant"));
    }

    bool AxolotlEntity::GetDataPlayingDead() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_playing_dead"));
    }

    bool AxolotlEntity::GetFromBucket() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("from_bucket"));
    }


    void AxolotlEntity::SetDataVariant(const int data_variant)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant"), data_variant);
    }

    void AxolotlEntity::SetDataPlayingDead(const bool data_playing_dead)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_playing_dead"), data_playing_dead);
    }

    void AxolotlEntity::SetFromBucket(const bool from_bucket)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("from_bucket"), from_bucket);
    }


    double AxolotlEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }


    double AxolotlEntity::GetWidthImpl() const
    {
        return 0.75;
    }

    double AxolotlEntity::GetHeightImpl() const
    {
        return 0.42;
    }

}
#endif
