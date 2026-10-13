#include "botcraft/Game/Entities/entities/animal/chicken/ChickenEntity.hpp"

namespace Botcraft
{
    ChickenEntity::ChickenEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        SetDataVariantId(0);
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        SetDataSoundVariantId(0);
#endif
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 4.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
    }

    ChickenEntity::~ChickenEntity()
    {

    }


    std::string ChickenEntity::GetName() const
    {
        return "chicken";
    }

    EntityType ChickenEntity::GetType() const
    {
        return EntityType::Chicken;
    }


    std::string ChickenEntity::GetClassName()
    {
        return "chicken";
    }

    EntityType ChickenEntity::GetClassType()
    {
        return EntityType::Chicken;
    }

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    ProtocolCraft::Json::Value ChickenEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();
        output["metadata"]["data_variant_id"] = GetDataVariantId();
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        output["metadata"]["data_sound_variant_id"] = GetDataSoundVariantId();
#endif

        return output;
    }

    int ChickenEntity::GetDataVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"));
    }

#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    int ChickenEntity::GetDataSoundVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_sound_variant_id"));
    }
#endif


    void ChickenEntity::SetDataVariantId(const int data_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"), data_variant_id);
    }

#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    void ChickenEntity::SetDataSoundVariantId(const int data_sound_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_sound_variant_id"), data_sound_variant_id);
    }
#endif
#endif

    double ChickenEntity::GetWidthImpl() const
    {
        return 0.4;
    }

    double ChickenEntity::GetHeightImpl() const
    {
        return 0.7;
    }

}
