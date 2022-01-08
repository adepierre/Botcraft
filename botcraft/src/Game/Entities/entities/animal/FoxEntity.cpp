#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/animal/FoxEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, FoxEntity::metadata_count> FoxEntity::metadata_names{ {
        "data_type_id",
        "data_flags_id",
        "data_trusted_id_0",
        "data_trusted_id_1",
    } };

    FoxEntity::FoxEntity()
    {
        // Initialize all metadata with default values
        SetDataTypeId(0);
        SetDataFlagsId(0);
        SetDataTrustedId0(std::optional<ProtocolCraft::UUID>());
        SetDataTrustedId1(std::optional<ProtocolCraft::UUID>());
    }

    FoxEntity::~FoxEntity()
    {

    }


    std::string FoxEntity::GetName() const
    {
        return "Fox";
    }

    EntityType FoxEntity::GetType() const
    {
        return EntityType::Fox;
    }

    AABB FoxEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double FoxEntity::GetWidth() const
    {
        return 0.6;
    }

    double FoxEntity::GetHeight() const
    {
        return 0.7;
    }


    std::string FoxEntity::GetClassName()
    {
        return "Fox";
    }

    EntityType FoxEntity::GetClassType()
    {
        return EntityType::Fox;
    }


    nlohmann::json FoxEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

        output["metadata"]["data_type_id"] = GetDataTypeId();
        output["metadata"]["data_flags_id"] = GetDataFlagsId();
        output["metadata"]["data_trusted_id_0"] = GetDataTrustedId0() ? nlohmann::json(GetDataTrustedId0().value()) : nlohmann::json();
        output["metadata"]["data_trusted_id_1"] = GetDataTrustedId1() ? nlohmann::json(GetDataTrustedId1().value()) : nlohmann::json();

        return output;
    }


    void FoxEntity::SetMetadataValue(const int index, const std::any& value)
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

    int FoxEntity::GetDataTypeId() const
    {
        return std::any_cast<int>(metadata.at("data_type_id"));
    }

    char FoxEntity::GetDataFlagsId() const
    {
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }

    const std::optional<ProtocolCraft::UUID>& FoxEntity::GetDataTrustedId0() const
    {
        return std::any_cast<const std::optional<ProtocolCraft::UUID>&>(metadata.at("data_trusted_id_0"));
    }

    const std::optional<ProtocolCraft::UUID>& FoxEntity::GetDataTrustedId1() const
    {
        return std::any_cast<const std::optional<ProtocolCraft::UUID>&>(metadata.at("data_trusted_id_1"));
    }


    void FoxEntity::SetDataTypeId(const int data_type_id)
    {
        metadata["data_type_id"] = data_type_id;
    }

    void FoxEntity::SetDataFlagsId(const char data_flags_id)
    {
        metadata["data_flags_id"] = data_flags_id;
    }

    void FoxEntity::SetDataTrustedId0(const std::optional<ProtocolCraft::UUID>& data_trusted_id_0)
    {
        metadata["data_trusted_id_0"] = data_trusted_id_0;
    }

    void FoxEntity::SetDataTrustedId1(const std::optional<ProtocolCraft::UUID>& data_trusted_id_1)
    {
        metadata["data_trusted_id_1"] = data_trusted_id_1;
    }

}
#endif