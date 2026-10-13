#include "botcraft/Game/Entities/entities/ambient/BatEntity.hpp"

namespace Botcraft
{
    BatEntity::BatEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataIdFlags(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 6.0) });
    }

    BatEntity::~BatEntity()
    {

    }


    std::string BatEntity::GetName() const
    {
        return "bat";
    }

    EntityType BatEntity::GetType() const
    {
        return EntityType::Bat;
    }


    std::string BatEntity::GetClassName()
    {
        return "bat";
    }

    EntityType BatEntity::GetClassType()
    {
        return EntityType::Bat;
    }


    ProtocolCraft::Json::Value BatEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AmbientCreatureEntity::Serialize();

        output["metadata"]["data_id_flags"] = GetDataIdFlags();

        return output;
    }


    char BatEntity::GetDataIdFlags() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_flags"));
    }


    void BatEntity::SetDataIdFlags(const char data_id_flags)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_flags"), data_id_flags);
    }


    double BatEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double BatEntity::GetHeightImpl() const
    {
        return 0.9;
    }

}
