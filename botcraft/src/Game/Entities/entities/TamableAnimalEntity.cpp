#include "botcraft/Game/Entities/entities/TamableAnimalEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, TamableAnimalEntity::metadata_count> TamableAnimalEntity::metadata_names{ {
        "data_flags_id",
        "data_owneruuid_id",
    } };

    TamableAnimalEntity::TamableAnimalEntity()
    {
        // Initialize all metadata with default values
        SetDataFlagsId(0);
        SetDataOwneruuidId(std::optional<ProtocolCraft::UUID>());
    }

    TamableAnimalEntity::~TamableAnimalEntity()
    {

    }

    bool TamableAnimalEntity::IsTamableAnimal() const
    {
        return true;
    }


    ProtocolCraft::Json::Value TamableAnimalEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_flags_id"] = GetDataFlagsId();
        output["metadata"]["data_owneruuid_id"] = GetDataOwneruuidId() ? ProtocolCraft::Json::Value(GetDataOwneruuidId().value()) : ProtocolCraft::Json::Value();

        return output;
    }


    void TamableAnimalEntity::SetMetadataValue(const int index, const std::any& value)
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

    char TamableAnimalEntity::GetDataFlagsId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }

    const std::optional<ProtocolCraft::UUID>& TamableAnimalEntity::GetDataOwneruuidId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const std::optional<ProtocolCraft::UUID>&>(metadata.at("data_owneruuid_id"));
    }


    void TamableAnimalEntity::SetDataFlagsId(const char data_flags_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_flags_id"] = data_flags_id;
    }

    void TamableAnimalEntity::SetDataOwneruuidId(const std::optional<ProtocolCraft::UUID>& data_owneruuid_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_owneruuid_id"] = data_owneruuid_id;
    }

}
