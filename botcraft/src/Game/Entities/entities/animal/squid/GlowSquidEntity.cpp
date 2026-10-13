#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "botcraft/Game/Entities/entities/animal/squid/GlowSquidEntity.hpp"

namespace Botcraft
{
    GlowSquidEntity::GlowSquidEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    int GlowSquidEntity::GetDataDarkTicksRemaining() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_dark_ticks_remaining"));
    }


    void GlowSquidEntity::SetDataDarkTicksRemaining(const int data_dark_ticks_remaining)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_dark_ticks_remaining"), data_dark_ticks_remaining);
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
