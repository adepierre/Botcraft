#pragma once

#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/raid/RaiderEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 404
    class AbstractIllagerEntity : public RaiderEntity
#else
    class AbstractIllagerEntity : public MonsterEntity
#endif
    {
    protected:
#if PROTOCOL_VERSION > 404
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#endif
#if PROTOCOL_VERSION > 404
        static constexpr int hierarchy_metadata_count = RaiderEntity::metadata_count + RaiderEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;
#endif

    public:
        AbstractIllagerEntity();
        virtual ~AbstractIllagerEntity();

        virtual bool IsAbstractIllager() const override;


#if PROTOCOL_VERSION < 405
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        char GetHasTarget() const;

        void SetHasTarget(const char has_target);
#endif
    };
}
