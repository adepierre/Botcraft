#include "botcraft/Game/Entities/entities/TamableAnimalEntity.hpp"

namespace Botcraft
{
    TamableAnimalEntity::TamableAnimalEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    char TamableAnimalEntity::GetDataFlagsId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_flags_id"));
    }

    std::optional<ProtocolCraft::UUID> TamableAnimalEntity::GetDataOwneruuidId() const
    {
        return GetMetadata<std::optional<ProtocolCraft::UUID>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_owneruuid_id"));
    }


    void TamableAnimalEntity::SetDataFlagsId(const char data_flags_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_flags_id"), data_flags_id);
    }

    void TamableAnimalEntity::SetDataOwneruuidId(const std::optional<ProtocolCraft::UUID>& data_owneruuid_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_owneruuid_id"), data_owneruuid_id);
    }

}
