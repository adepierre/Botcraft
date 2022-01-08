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


    nlohmann::json TamableAnimalEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

        output["data_flags_id"] = GetDataFlagsId();
        output["data_owneruuid_id"] = GetDataOwneruuidId() ? nlohmann::json(GetDataOwneruuidId().value()) : nlohmann::json();

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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char TamableAnimalEntity::GetDataFlagsId() const
    {
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }

    const std::optional<ProtocolCraft::UUID>& TamableAnimalEntity::GetDataOwneruuidId() const
    {
        return std::any_cast<const std::optional<ProtocolCraft::UUID>&>(metadata.at("data_owneruuid_id"));
    }


    void TamableAnimalEntity::SetDataFlagsId(const char data_flags_id)
    {
        metadata["data_flags_id"] = data_flags_id;
    }

    void TamableAnimalEntity::SetDataOwneruuidId(const std::optional<ProtocolCraft::UUID>& data_owneruuid_id)
    {
        metadata["data_owneruuid_id"] = data_owneruuid_id;
    }

}
