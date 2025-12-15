#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/squid/SquidEntity.hpp"

namespace Botcraft
{
    class GlowSquidEntity : public SquidEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = SquidEntity::metadata_count + SquidEntity::hierarchy_metadata_count;

    public:
        GlowSquidEntity();
        virtual ~GlowSquidEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataDarkTicksRemaining() const;

        void SetDataDarkTicksRemaining(const int data_dark_ticks_remaining);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
