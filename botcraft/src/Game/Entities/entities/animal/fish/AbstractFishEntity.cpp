#include "botcraft/Game/Entities/entities/animal/fish/AbstractFishEntity.hpp"

namespace Botcraft
{
    AbstractFishEntity::AbstractFishEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetFromBucket(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 3.0) });
    }

    AbstractFishEntity::~AbstractFishEntity()
    {

    }

    bool AbstractFishEntity::IsAbstractFish() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractFishEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = WaterAnimalEntity::Serialize();

        output["metadata"]["from_bucket"] = GetFromBucket();

        return output;
    }


    bool AbstractFishEntity::GetFromBucket() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("from_bucket"));
    }


    void AbstractFishEntity::SetFromBucket(const bool from_bucket)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("from_bucket"), from_bucket);
    }

}
