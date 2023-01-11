#include "botcraft/Game/Entities/entities/animal/horse/HorseEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, HorseEntity::metadata_count> HorseEntity::metadata_names{ {
        "data_id_type_variant",
#if PROTOCOL_VERSION < 405
        "armor_type",
#endif
    } };

    HorseEntity::HorseEntity()
    {
        // Initialize all metadata with default values
        SetDataIdTypeVariant(0);
#if PROTOCOL_VERSION < 405
        SetArmorType(std::optional<int>());
#endif
    }

    HorseEntity::~HorseEntity()
    {

    }


    std::string HorseEntity::GetName() const
    {
        return "Horse";
    }

    EntityType HorseEntity::GetType() const
    {
        return EntityType::Horse;
    }

    double HorseEntity::GetWidth() const
    {
        return 1.3964844;
    }

    double HorseEntity::GetHeight() const
    {
        return 1.6;
    }


    std::string HorseEntity::GetClassName()
    {
        return "Horse";
    }

    EntityType HorseEntity::GetClassType()
    {
        return EntityType::Horse;
    }


    ProtocolCraft::Json::Value HorseEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractHorseEntity::Serialize();

        output["metadata"]["data_id_type_variant"] = GetDataIdTypeVariant();
#if PROTOCOL_VERSION < 405
        output["metadata"]["armor_type"] = GetArmorType() ? ProtocolCraft::Json::Value(GetArmorType().value()) : ProtocolCraft::Json::Value();
#endif

        return output;
    }


    void HorseEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractHorseEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int HorseEntity::GetDataIdTypeVariant() const
    {
        return std::any_cast<int>(metadata.at("data_id_type_variant"));
    }

#if PROTOCOL_VERSION < 405
    const std::optional<int>& HorseEntity::GetArmorType() const
    {
        return std::any_cast<const std::optional<int>&>(metadata.at("armor_type"));
    }
#endif


    void HorseEntity::SetDataIdTypeVariant(const int data_id_type_variant)
    {
        metadata["data_id_type_variant"] = data_id_type_variant;
    }

#if PROTOCOL_VERSION < 405
    void HorseEntity::SetArmorType(const std::optional<int>& armor_type)
    {
        metadata["armor_type"] = armor_type;
    }
#endif

}
