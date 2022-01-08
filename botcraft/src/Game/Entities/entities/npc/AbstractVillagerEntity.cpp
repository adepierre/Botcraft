#if PROTOCOL_VERSION > 477
#include "botcraft/Game/Entities/entities/npc/AbstractVillagerEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, AbstractVillagerEntity::metadata_count> AbstractVillagerEntity::metadata_names{ {
        "data_unhappy_counter",
    } };

    AbstractVillagerEntity::AbstractVillagerEntity()
    {
        // Initialize all metadata with default values
        SetDataUnhappyCounter(0);
    }

    AbstractVillagerEntity::~AbstractVillagerEntity()
    {

    }

    bool AbstractVillagerEntity::IsAbstractVillager() const
    {
        return true;
    }


    nlohmann::json AbstractVillagerEntity::Serialize() const
    {
        nlohmann::json output = AgeableMobEntity::Serialize();

        output["metadata"]["data_unhappy_counter"] = GetDataUnhappyCounter();

        return output;
    }


    void AbstractVillagerEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AgeableMobEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int AbstractVillagerEntity::GetDataUnhappyCounter() const
    {
        return std::any_cast<int>(metadata.at("data_unhappy_counter"));
    }


    void AbstractVillagerEntity::SetDataUnhappyCounter(const int data_unhappy_counter)
    {
        metadata["data_unhappy_counter"] = data_unhappy_counter;
    }

}
#endif
