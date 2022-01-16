#include "botcraft/Game/Entities/entities/projectile/WitherSkullEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, WitherSkullEntity::metadata_count> WitherSkullEntity::metadata_names{ {
        "data_dangerous",
    } };

    WitherSkullEntity::WitherSkullEntity()
    {
        // Initialize all metadata with default values
        SetDataDangerous(false);
    }

    WitherSkullEntity::~WitherSkullEntity()
    {

    }


    std::string WitherSkullEntity::GetName() const
    {
        return "WitherSkull";
    }

    EntityType WitherSkullEntity::GetType() const
    {
        return EntityType::WitherSkull;
    }

    double WitherSkullEntity::GetWidth() const
    {
        return 0.3125;
    }

    double WitherSkullEntity::GetHeight() const
    {
        return 0.3125;
    }


    std::string WitherSkullEntity::GetClassName()
    {
        return "WitherSkull";
    }

    EntityType WitherSkullEntity::GetClassType()
    {
        return EntityType::WitherSkull;
    }


    nlohmann::json WitherSkullEntity::Serialize() const
    {
        nlohmann::json output = AbstractHurtingProjectileEntity::Serialize();

        output["metadata"]["data_dangerous"] = GetDataDangerous();

        return output;
    }


    void WitherSkullEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractHurtingProjectileEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool WitherSkullEntity::GetDataDangerous() const
    {
        return std::any_cast<bool>(metadata.at("data_dangerous"));
    }


    void WitherSkullEntity::SetDataDangerous(const bool data_dangerous)
    {
        metadata["data_dangerous"] = data_dangerous;
    }

}
