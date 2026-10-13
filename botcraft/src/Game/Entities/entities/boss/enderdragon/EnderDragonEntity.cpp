#include "botcraft/Game/Entities/entities/boss/enderdragon/EnderDragonEntity.hpp"

namespace Botcraft
{
    EnderDragonEntity::EnderDragonEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataPhase(10);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 200.0) });
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        attributes.insert({ EntityAttribute::Type::CameraDistance, EntityAttribute(EntityAttribute::Type::CameraDistance, 16.0) });
#endif
    }

    EnderDragonEntity::~EnderDragonEntity()
    {

    }


    std::string EnderDragonEntity::GetName() const
    {
        return "ender_dragon";
    }

    EntityType EnderDragonEntity::GetType() const
    {
        return EntityType::EnderDragon;
    }


    std::string EnderDragonEntity::GetClassName()
    {
        return "ender_dragon";
    }

    EntityType EnderDragonEntity::GetClassType()
    {
        return EntityType::EnderDragon;
    }


    ProtocolCraft::Json::Value EnderDragonEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MobEntity::Serialize();

        output["metadata"]["data_phase"] = GetDataPhase();

        return output;
    }


    int EnderDragonEntity::GetDataPhase() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_phase"));
    }


    void EnderDragonEntity::SetDataPhase(const int data_phase)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_phase"), data_phase);
    }


    double EnderDragonEntity::GetWidthImpl() const
    {
        return 16.0;
    }

    double EnderDragonEntity::GetHeightImpl() const
    {
        return 8.0;
    }

}
