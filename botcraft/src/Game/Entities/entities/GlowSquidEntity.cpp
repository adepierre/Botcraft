#if PROTOCOL_VERSION > 754
#include "botcraft/Game/Entities/entities/GlowSquidEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, GlowSquidEntity::metadata_count> GlowSquidEntity::metadata_names{ {
        "data_dark_ticks_remaining",
    } };

    GlowSquidEntity::GlowSquidEntity()
    {
        // Initialize all metadata with default values
        SetDataDarkTicksRemaining(0);
    }

    GlowSquidEntity::~GlowSquidEntity()
    {

    }


    std::string GlowSquidEntity::GetName() const
    {
        return "GlowSquid";
    }

    EntityType GlowSquidEntity::GetType() const
    {
        return EntityType::GlowSquid;
    }

    AABB GlowSquidEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double GlowSquidEntity::GetWidth() const
    {
        return 0.8;
    }

    double GlowSquidEntity::GetHeight() const
    {
        return 0.8;
    }


    std::string GlowSquidEntity::GetClassName()
    {
        return "GlowSquid";
    }

    EntityType GlowSquidEntity::GetClassType()
    {
        return EntityType::GlowSquid;
    }


    nlohmann::json GlowSquidEntity::Serialize() const
    {
        nlohmann::json output = SquidEntity::Serialize();

        output["metadata"]["data_dark_ticks_remaining"] = GetDataDarkTicksRemaining();

        return output;
    }


    void GlowSquidEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            SquidEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int GlowSquidEntity::GetDataDarkTicksRemaining() const
    {
        return std::any_cast<int>(metadata.at("data_dark_ticks_remaining"));
    }


    void GlowSquidEntity::SetDataDarkTicksRemaining(const int data_dark_ticks_remaining)
    {
        metadata["data_dark_ticks_remaining"] = data_dark_ticks_remaining;
    }

}
#endif
