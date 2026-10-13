#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "botcraft/Game/Entities/entities/animal/frog/TadpoleEntity.hpp"

namespace Botcraft
{
    TadpoleEntity::TadpoleEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        SetAgeLocked(false);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 1.0) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 6.0) });
    }

    TadpoleEntity::~TadpoleEntity()
    {

    }


    std::string TadpoleEntity::GetName() const
    {
        return "tadpole";
    }

    EntityType TadpoleEntity::GetType() const
    {
        return EntityType::Tadpole;
    }


    std::string TadpoleEntity::GetClassName()
    {
        return "tadpole";
    }

    EntityType TadpoleEntity::GetClassType()
    {
        return EntityType::Tadpole;
    }


#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    ProtocolCraft::Json::Value TadpoleEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractFishEntity::Serialize();

        output["metadata"]["age_locked"] = GetAgeLocked();

        return output;
    }


    bool TadpoleEntity::GetAgeLocked() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("age_locked"));
    }


    void TadpoleEntity::SetAgeLocked(const bool age_locked)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("age_locked"), age_locked);
    }
#endif


    double TadpoleEntity::GetWidthImpl() const
    {
        return 0.4;
    }

    double TadpoleEntity::GetHeightImpl() const
    {
        return 0.3;
    }

}
#endif
