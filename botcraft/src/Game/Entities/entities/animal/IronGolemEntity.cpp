#include "botcraft/Game/Entities/entities/animal/IronGolemEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, IronGolemEntity::metadata_count> IronGolemEntity::metadata_names{ {
        "data_flags_id",
    } };

    IronGolemEntity::IronGolemEntity()
    {
        // Initialize all metadata with default values
        SetDataFlagsId(0);
    }

    IronGolemEntity::~IronGolemEntity()
    {

    }


    std::string IronGolemEntity::GetName() const
    {
        return "IronGolem";
    }

    EntityType IronGolemEntity::GetType() const
    {
        return EntityType::IronGolem;
    }

    AABB IronGolemEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double IronGolemEntity::GetWidth() const
    {
        return 1.4;
    }

    double IronGolemEntity::GetHeight() const
    {
        return 2.7;
    }


    std::string IronGolemEntity::GetClassName()
    {
        return "IronGolem";
    }

    EntityType IronGolemEntity::GetClassType()
    {
        return EntityType::IronGolem;
    }


    nlohmann::json IronGolemEntity::Serialize() const
    {
        nlohmann::json output = AbstractGolemEntity::Serialize();

        output["data_flags_id"] = GetDataFlagsId();

        return output;
    }


    void IronGolemEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractGolemEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char IronGolemEntity::GetDataFlagsId() const
    {
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }


    void IronGolemEntity::SetDataFlagsId(const char data_flags_id)
    {
        metadata["data_flags_id"] = data_flags_id;
    }

}
