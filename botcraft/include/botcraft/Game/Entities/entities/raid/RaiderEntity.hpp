#if PROTOCOL_VERSION > 404
#pragma once

#include "botcraft/Game/Entities/entities/monster/PatrollingMonsterEntity.hpp"

namespace Botcraft
{
    class RaiderEntity : public PatrollingMonsterEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = PatrollingMonsterEntity::metadata_count + PatrollingMonsterEntity::hierarchy_metadata_count;

    public:
        RaiderEntity();
        virtual ~RaiderEntity();

        virtual bool IsRaider() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetIsCelebrating() const;

        void SetIsCelebrating(const bool is_celebrating);

    };
}
#endif
