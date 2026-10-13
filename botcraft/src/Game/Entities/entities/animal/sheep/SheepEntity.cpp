#include "botcraft/Game/Entities/entities/animal/sheep/SheepEntity.hpp"

namespace Botcraft
{
    SheepEntity::SheepEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataWoolId(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 8.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.23) });
    }

    SheepEntity::~SheepEntity()
    {

    }


    std::string SheepEntity::GetName() const
    {
        return "sheep";
    }

    EntityType SheepEntity::GetType() const
    {
        return EntityType::Sheep;
    }


    std::string SheepEntity::GetClassName()
    {
        return "sheep";
    }

    EntityType SheepEntity::GetClassType()
    {
        return EntityType::Sheep;
    }


    ProtocolCraft::Json::Value SheepEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_wool_id"] = GetDataWoolId();

        return output;
    }


    char SheepEntity::GetDataWoolId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_wool_id"));
    }


    void SheepEntity::SetDataWoolId(const char data_wool_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_wool_id"), data_wool_id);
    }


    double SheepEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double SheepEntity::GetHeightImpl() const
    {
        return 1.3;
    }

}
