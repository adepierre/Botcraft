#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/Entities/entities/monster/skeleton/BoggedEntity.hpp"

namespace Botcraft
{
    BoggedEntity::BoggedEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataSheared(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 16.0) });
    }

    BoggedEntity::~BoggedEntity()
    {

    }


    std::string BoggedEntity::GetName() const
    {
        return "bogged";
    }

    EntityType BoggedEntity::GetType() const
    {
        return EntityType::Bogged;
    }


    std::string BoggedEntity::GetClassName()
    {
        return "bogged";
    }

    EntityType BoggedEntity::GetClassType()
    {
        return EntityType::Bogged;
    }


    ProtocolCraft::Json::Value BoggedEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractSkeletonEntity::Serialize();

        output["metadata"]["data_sheared"] = GetDataSheared();

        return output;
    }


    bool BoggedEntity::GetDataSheared() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_sheared"));
    }


    void BoggedEntity::SetDataSheared(const bool data_sheared)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_sheared"), data_sheared);
    }


    double BoggedEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double BoggedEntity::GetHeightImpl() const
    {
        return 1.99;
    }

}
#endif
