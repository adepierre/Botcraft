#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#include "botcraft/Game/Entities/entities/animal/nautilus/ZombieNautilusEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, ZombieNautilusEntity::metadata_count> ZombieNautilusEntity::metadata_names{ {
        "data_variant_id",
    } };

    ZombieNautilusEntity::ZombieNautilusEntity()
    {
        // Initialize all metadata with default values
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


    void ZombieNautilusEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractNautilusEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int ZombieNautilusEntity::GetDataVariantId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_variant_id"));
    }


    void ZombieNautilusEntity::SetDataVariantId(const int data_variant_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_variant_id"] = data_variant_id;
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
