#include "botcraft/Game/Entities/entities/animal/equine/AbstractChestedHorseEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, AbstractChestedHorseEntity::metadata_count> AbstractChestedHorseEntity::metadata_names{ {
        "data_id_chest",
    } };

    AbstractChestedHorseEntity::AbstractChestedHorseEntity()
    {
        // Initialize all metadata with default values
        SetDataIdChest(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.175) });
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        attributes.insert({ EntityAttribute::Type::HorseJumpStrength, EntityAttribute(EntityAttribute::Type::HorseJumpStrength, 0.5) });
#else
        attributes.insert({ EntityAttribute::Type::JumpStrength, EntityAttribute(EntityAttribute::Type::JumpStrength, 0.5) });
#endif
    }

    AbstractChestedHorseEntity::~AbstractChestedHorseEntity()
    {

    }

    bool AbstractChestedHorseEntity::IsAbstractChestedHorse() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractChestedHorseEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractHorseEntity::Serialize();

        output["metadata"]["data_id_chest"] = GetDataIdChest();

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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool AbstractChestedHorseEntity::GetDataIdChest() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_id_chest"));
    }


    void AbstractChestedHorseEntity::SetDataIdChest(const bool data_id_chest)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_chest"] = data_id_chest;
    }

}
