#include "botcraft/Game/Entities/entities/animal/pig/PigEntity.hpp"

namespace Botcraft
{
    PigEntity::PigEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SetDataSaddleId(false);
#endif
        SetDataBoostTime(0);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        SetDataVariantId(0);
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        SetDataSoundVariantId(0);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
    }

    PigEntity::~PigEntity()
    {

    }


    std::string PigEntity::GetName() const
    {
        return "pig";
    }

    EntityType PigEntity::GetType() const
    {
        return EntityType::Pig;
    }


    std::string PigEntity::GetClassName()
    {
        return "pig";
    }

    EntityType PigEntity::GetClassType()
    {
        return EntityType::Pig;
    }


    ProtocolCraft::Json::Value PigEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        output["metadata"]["data_saddle_id"] = GetDataSaddleId();
#endif
        output["metadata"]["data_boost_time"] = GetDataBoostTime();
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        output["metadata"]["data_variant_id"] = GetDataVariantId();
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        output["metadata"]["data_sound_variant_id"] = GetDataSoundVariantId();
#endif

        return output;
    }


#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    bool PigEntity::GetDataSaddleId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_saddle_id"));
    }
#endif

    int PigEntity::GetDataBoostTime() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_boost_time"));
    }

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    int PigEntity::GetDataVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"));
    }
#endif

#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    int PigEntity::GetDataSoundVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_sound_variant_id"));
    }
#endif


#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    void PigEntity::SetDataSaddleId(const bool data_saddle_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_saddle_id"), data_saddle_id);
    }
#endif

    void PigEntity::SetDataBoostTime(const int data_boost_time)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_boost_time"), data_boost_time);
    }

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    void PigEntity::SetDataVariantId(const int data_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"), data_variant_id);
    }
#endif

#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    void PigEntity::SetDataSoundVariantId(const int data_sound_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_sound_variant_id"), data_sound_variant_id);
    }
#endif


    double PigEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double PigEntity::GetHeightImpl() const
    {
        return 0.9;
    }

}
