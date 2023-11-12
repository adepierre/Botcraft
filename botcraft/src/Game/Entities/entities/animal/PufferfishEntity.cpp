#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/animal/PufferfishEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, PufferfishEntity::metadata_count> PufferfishEntity::metadata_names{ {
        "puff_state",
    } };

    PufferfishEntity::PufferfishEntity()
    {
        // Initialize all metadata with default values
        SetPuffState(0);
    }

    PufferfishEntity::~PufferfishEntity()
    {

    }


    std::string PufferfishEntity::GetName() const
    {
        return "pufferfish";
    }

    EntityType PufferfishEntity::GetType() const
    {
        return EntityType::Pufferfish;
    }


    std::string PufferfishEntity::GetClassName()
    {
        return "pufferfish";
    }

    EntityType PufferfishEntity::GetClassType()
    {
        return EntityType::Pufferfish;
    }


    ProtocolCraft::Json::Value PufferfishEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractFishEntity::Serialize();

        output["metadata"]["puff_state"] = GetPuffState();

        return output;
    }


    void PufferfishEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractFishEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int PufferfishEntity::GetPuffState() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("puff_state"));
    }


    void PufferfishEntity::SetPuffState(const int puff_state)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["puff_state"] = puff_state;
    }


    double PufferfishEntity::GetWidthImpl() const
    {
        return 0.7;
    }

    double PufferfishEntity::GetHeightImpl() const
    {
        return 0.7;
    }

}
#endif
