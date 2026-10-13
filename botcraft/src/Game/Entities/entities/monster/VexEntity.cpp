#include "botcraft/Game/Entities/entities/monster/VexEntity.hpp"

namespace Botcraft
{
    VexEntity::VexEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataFlagsId(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 14.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 4.0) });
    }

    VexEntity::~VexEntity()
    {

    }


    std::string VexEntity::GetName() const
    {
        return "vex";
    }

    EntityType VexEntity::GetType() const
    {
        return EntityType::Vex;
    }


    std::string VexEntity::GetClassName()
    {
        return "vex";
    }

    EntityType VexEntity::GetClassType()
    {
        return EntityType::Vex;
    }


    ProtocolCraft::Json::Value VexEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_flags_id"] = GetDataFlagsId();

        return output;
    }


    char VexEntity::GetDataFlagsId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_flags_id"));
    }


    void VexEntity::SetDataFlagsId(const char data_flags_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_flags_id"), data_flags_id);
    }


    double VexEntity::GetWidthImpl() const
    {
        return 0.4;
    }

    double VexEntity::GetHeightImpl() const
    {
        return 0.8;
    }

}
