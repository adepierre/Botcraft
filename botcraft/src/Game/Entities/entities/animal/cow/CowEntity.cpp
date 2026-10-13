#include "botcraft/Game/Entities/entities/animal/cow/CowEntity.hpp"

namespace Botcraft
{
    CowEntity::CowEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        SetDataVariantId(0);
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        SetDataSoundVariantId(0);
#endif
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
#endif
    }

    CowEntity::~CowEntity()
    {

    }


    std::string CowEntity::GetName() const
    {
        return "cow";
    }

    EntityType CowEntity::GetType() const
    {
        return EntityType::Cow;
    }


    std::string CowEntity::GetClassName()
    {
        return "cow";
    }

    EntityType CowEntity::GetClassType()
    {
        return EntityType::Cow;
    }

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    ProtocolCraft::Json::Value CowEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractCowEntity::Serialize();
        output["metadata"]["data_variant_id"] = GetDataVariantId();
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        output["metadata"]["data_sound_variant_id"] = GetDataSoundVariantId();
#endif

        return output;
    }

    int CowEntity::GetDataVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"));
    }
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    int CowEntity::GetDataSoundVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_sound_variant_id"));
    }
#endif


    void CowEntity::SetDataVariantId(const int data_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"), data_variant_id);
    }
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    void CowEntity::SetDataSoundVariantId(const int data_sound_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_sound_variant_id"), data_sound_variant_id);
    }
#endif
#endif


    double CowEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double CowEntity::GetHeightImpl() const
    {
        return 1.4;
    }

}
