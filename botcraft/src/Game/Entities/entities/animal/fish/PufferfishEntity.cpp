#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/animal/fish/PufferfishEntity.hpp"

namespace Botcraft
{
    PufferfishEntity::PufferfishEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    int PufferfishEntity::GetPuffState() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("puff_state"));
    }


    void PufferfishEntity::SetPuffState(const int puff_state)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("puff_state"), puff_state);
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
