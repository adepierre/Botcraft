#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/monster/hoglin/HoglinEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, HoglinEntity::metadata_count> HoglinEntity::metadata_names{ {
        "data_immune_to_zombification",
    } };

    HoglinEntity::HoglinEntity()
    {
        // Initialize all metadata with default values
        SetDataImmuneToZombification(false);
    }

    HoglinEntity::~HoglinEntity()
    {

    }


    std::string HoglinEntity::GetName() const
    {
        return "hoglin";
    }

    EntityType HoglinEntity::GetType() const
    {
        return EntityType::Hoglin;
    }

    double HoglinEntity::GetWidth() const
    {
        return 1.3964844;
    }

    double HoglinEntity::GetHeight() const
    {
        return 1.4;
    }


    std::string HoglinEntity::GetClassName()
    {
        return "hoglin";
    }

    EntityType HoglinEntity::GetClassType()
    {
        return EntityType::Hoglin;
    }


    ProtocolCraft::Json::Value HoglinEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_immune_to_zombification"] = GetDataImmuneToZombification();

        return output;
    }


    void HoglinEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool HoglinEntity::GetDataImmuneToZombification() const
    {
        return std::any_cast<bool>(metadata.at("data_immune_to_zombification"));
    }


    void HoglinEntity::SetDataImmuneToZombification(const bool data_immune_to_zombification)
    {
        metadata["data_immune_to_zombification"] = data_immune_to_zombification;
    }

}
#endif
