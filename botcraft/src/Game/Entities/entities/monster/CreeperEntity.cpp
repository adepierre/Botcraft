#include "botcraft/Game/Entities/entities/monster/CreeperEntity.hpp"

namespace Botcraft
{
    CreeperEntity::CreeperEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataSwellDir(-1);
        SetDataIsPowered(false);
        SetDataIsIgnited(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
    }

    CreeperEntity::~CreeperEntity()
    {

    }


    std::string CreeperEntity::GetName() const
    {
        return "creeper";
    }

    EntityType CreeperEntity::GetType() const
    {
        return EntityType::Creeper;
    }


    std::string CreeperEntity::GetClassName()
    {
        return "creeper";
    }

    EntityType CreeperEntity::GetClassType()
    {
        return EntityType::Creeper;
    }


    ProtocolCraft::Json::Value CreeperEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_swell_dir"] = GetDataSwellDir();
        output["metadata"]["data_is_powered"] = GetDataIsPowered();
        output["metadata"]["data_is_ignited"] = GetDataIsIgnited();

        return output;
    }


    int CreeperEntity::GetDataSwellDir() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_swell_dir"));
    }

    bool CreeperEntity::GetDataIsPowered() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_powered"));
    }

    bool CreeperEntity::GetDataIsIgnited() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_ignited"));
    }


    void CreeperEntity::SetDataSwellDir(const int data_swell_dir)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_swell_dir"), data_swell_dir);
    }

    void CreeperEntity::SetDataIsPowered(const bool data_is_powered)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_powered"), data_is_powered);
    }

    void CreeperEntity::SetDataIsIgnited(const bool data_is_ignited)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_ignited"), data_is_ignited);
    }


    double CreeperEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double CreeperEntity::GetHeightImpl() const
    {
        return 1.7;
    }

}
