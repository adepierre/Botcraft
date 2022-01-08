#include "botcraft/Game/Entities/entities/animal/horse/AbstractChestedHorseEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, AbstractChestedHorseEntity::metadata_count> AbstractChestedHorseEntity::metadata_names{ {
        "data_id_chest",
    } };

    AbstractChestedHorseEntity::AbstractChestedHorseEntity()
    {
        // Initialize all metadata with default values
        SetDataIdChest(false);
    }

    AbstractChestedHorseEntity::~AbstractChestedHorseEntity()
    {

    }

    bool AbstractChestedHorseEntity::IsAbstractChestedHorse() const
    {
        return true;
    }


    nlohmann::json AbstractChestedHorseEntity::Serialize() const
    {
        nlohmann::json output = AbstractHorseEntity::Serialize();

        output["data_id_chest"] = GetDataIdChest();

        return output;
    }


    void AbstractChestedHorseEntity::SetMetadataValue(const int index, const std::any& value)
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

    bool AbstractChestedHorseEntity::GetDataIdChest() const
    {
        return std::any_cast<bool>(metadata.at("data_id_chest"));
    }


    void AbstractChestedHorseEntity::SetDataIdChest(const bool data_id_chest)
    {
        metadata["data_id_chest"] = data_id_chest;
    }

}
