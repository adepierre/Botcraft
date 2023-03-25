#include "botcraft/Game/Entities/entities/animal/ParrotEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, ParrotEntity::metadata_count> ParrotEntity::metadata_names{ {
        "data_variant_id",
    } };

    ParrotEntity::ParrotEntity()
    {
        // Initialize all metadata with default values
        SetDataVariantId(0);
    }

    ParrotEntity::~ParrotEntity()
    {

    }


    std::string ParrotEntity::GetName() const
    {
        return "parrot";
    }

    EntityType ParrotEntity::GetType() const
    {
        return EntityType::Parrot;
    }

    double ParrotEntity::GetWidth() const
    {
        return 0.5;
    }

    double ParrotEntity::GetHeight() const
    {
        return 0.9;
    }


    std::string ParrotEntity::GetClassName()
    {
        return "parrot";
    }

    EntityType ParrotEntity::GetClassType()
    {
        return EntityType::Parrot;
    }


    ProtocolCraft::Json::Value ParrotEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = ShoulderRidingEntity::Serialize();

        output["metadata"]["data_variant_id"] = GetDataVariantId();

        return output;
    }


    void ParrotEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            ShoulderRidingEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int ParrotEntity::GetDataVariantId() const
    {
        return std::any_cast<int>(metadata.at("data_variant_id"));
    }


    void ParrotEntity::SetDataVariantId(const int data_variant_id)
    {
        metadata["data_variant_id"] = data_variant_id;
    }

}
