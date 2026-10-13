#include "botcraft/Game/Entities/entities/projectile/hurtingprojectile/WitherSkullEntity.hpp"

namespace Botcraft
{
    WitherSkullEntity::WitherSkullEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataDangerous(false);
    }

    WitherSkullEntity::~WitherSkullEntity()
    {

    }


    std::string WitherSkullEntity::GetName() const
    {
        return "wither_skull";
    }

    EntityType WitherSkullEntity::GetType() const
    {
        return EntityType::WitherSkull;
    }


    std::string WitherSkullEntity::GetClassName()
    {
        return "wither_skull";
    }

    EntityType WitherSkullEntity::GetClassType()
    {
        return EntityType::WitherSkull;
    }


    ProtocolCraft::Json::Value WitherSkullEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractHurtingProjectileEntity::Serialize();

        output["metadata"]["data_dangerous"] = GetDataDangerous();

        return output;
    }


    bool WitherSkullEntity::GetDataDangerous() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_dangerous"));
    }


    void WitherSkullEntity::SetDataDangerous(const bool data_dangerous)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_dangerous"), data_dangerous);
    }


    double WitherSkullEntity::GetWidthImpl() const
    {
        return 0.3125;
    }

    double WitherSkullEntity::GetHeightImpl() const
    {
        return 0.3125;
    }

}
