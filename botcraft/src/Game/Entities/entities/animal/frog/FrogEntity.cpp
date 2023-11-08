#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "botcraft/Game/Entities/entities/animal/frog/FrogEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, FrogEntity::metadata_count> FrogEntity::metadata_names{ {
        "data_variant_id",
        "data_tongue_target_id",
    } };

    FrogEntity::FrogEntity()
    {
        // Initialize all metadata with default values
        SetDataVariantId(0);
        SetDataTongueTargetId(std::optional<int>());
    }

    FrogEntity::~FrogEntity()
    {

    }


    std::string FrogEntity::GetName() const
    {
        return "frog";
    }

    EntityType FrogEntity::GetType() const
    {
        return EntityType::Frog;
    }

    double FrogEntity::GetWidth() const
    {
        return 0.5;
    }

    double FrogEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string FrogEntity::GetClassName()
    {
        return "frog";
    }

    EntityType FrogEntity::GetClassType()
    {
        return EntityType::Frog;
    }


    ProtocolCraft::Json::Value FrogEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_variant_id"] = GetDataVariantId();
        output["metadata"]["data_tongue_target_id"] = GetDataTongueTargetId() ? ProtocolCraft::Json::Value(GetDataTongueTargetId().value()) : ProtocolCraft::Json::Value();

        return output;
    }


    void FrogEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int FrogEntity::GetDataVariantId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_variant_id"));
    }

    std::optional<int> FrogEntity::GetDataTongueTargetId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<std::optional<int>>(metadata.at("data_tongue_target_id"));
    }


    void FrogEntity::SetDataVariantId(const int data_variant_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_variant_id"] = data_variant_id;
    }

    void FrogEntity::SetDataTongueTargetId(const std::optional<int>& data_tongue_target_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_tongue_target_id"] = data_tongue_target_id;
    }

}
#endif
