#include "botcraft/Game/Entities/entities/animal/golem/SnowGolemEntity.hpp"

namespace Botcraft
{
    SnowGolemEntity::SnowGolemEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataPumpkinId(16);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 4.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
    }

    SnowGolemEntity::~SnowGolemEntity()
    {

    }


    std::string SnowGolemEntity::GetName() const
    {
        return "snow_golem";
    }

    EntityType SnowGolemEntity::GetType() const
    {
        return EntityType::SnowGolem;
    }


    std::string SnowGolemEntity::GetClassName()
    {
        return "snow_golem";
    }

    EntityType SnowGolemEntity::GetClassType()
    {
        return EntityType::SnowGolem;
    }


    ProtocolCraft::Json::Value SnowGolemEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractGolemEntity::Serialize();

        output["metadata"]["data_pumpkin_id"] = GetDataPumpkinId();

        return output;
    }


    char SnowGolemEntity::GetDataPumpkinId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_pumpkin_id"));
    }


    void SnowGolemEntity::SetDataPumpkinId(const char data_pumpkin_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_pumpkin_id"), data_pumpkin_id);
    }


    double SnowGolemEntity::GetWidthImpl() const
    {
        return 0.7;
    }

    double SnowGolemEntity::GetHeightImpl() const
    {
        return 1.9;
    }

}
