#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "botcraft/Game/Entities/entities/GlowSquidEntity.hpp"

#include <mutex>

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
        return "glow_squid";
    }

    EntityType GlowSquidEntity::GetType() const
    {
        return EntityType::GlowSquid;
    }


    std::string GlowSquidEntity::GetClassName()
    {
        return "glow_squid";
    }

    EntityType GlowSquidEntity::GetClassType()
    {
        return EntityType::GlowSquid;
    }


    ProtocolCraft::Json::Value GlowSquidEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = SquidEntity::Serialize();

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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int GlowSquidEntity::GetDataDarkTicksRemaining() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_dark_ticks_remaining"));
    }


    void GlowSquidEntity::SetDataDarkTicksRemaining(const int data_dark_ticks_remaining)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_dark_ticks_remaining"] = data_dark_ticks_remaining;
    }


    double GlowSquidEntity::GetWidthImpl() const
    {
        return 0.8;
    }

    double GlowSquidEntity::GetHeightImpl() const
    {
        return 0.8;
    }

}
#endif
