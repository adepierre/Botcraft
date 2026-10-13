#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#include "botcraft/Game/Entities/entities/animal/nautilus/ZombieNautilusEntity.hpp"

namespace Botcraft
{
    ZombieNautilusEntity::ZombieNautilusEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataVariantId(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 1.1) });
    }

    ZombieNautilusEntity::~ZombieNautilusEntity()
    {

    }


    std::string ZombieNautilusEntity::GetName() const
    {
        return "zombie_nautilus";
    }

    EntityType ZombieNautilusEntity::GetType() const
    {
        return EntityType::ZombieNautilus;
    }


    std::string ZombieNautilusEntity::GetClassName()
    {
        return "zombie_nautilus";
    }

    EntityType ZombieNautilusEntity::GetClassType()
    {
        return EntityType::ZombieNautilus;
    }


    ProtocolCraft::Json::Value ZombieNautilusEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractNautilusEntity::Serialize();

        output["metadata"]["data_variant_id"] = GetDataVariantId();

        return output;
    }


    int ZombieNautilusEntity::GetDataVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"));
    }


    void ZombieNautilusEntity::SetDataVariantId(const int data_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"), data_variant_id);
    }


    double ZombieNautilusEntity::GetWidthImpl() const
    {
        return 0.875;
    }

    double ZombieNautilusEntity::GetHeightImpl() const
    {
        return 0.95;
    }

}
#endif
