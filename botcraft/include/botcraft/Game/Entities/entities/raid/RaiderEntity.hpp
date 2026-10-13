#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#pragma once

#include "botcraft/Game/Entities/entities/monster/PatrollingMonsterEntity.hpp"

namespace Botcraft
{
    class RaiderEntity : public PatrollingMonsterEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("is_celebrating"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = PatrollingMonsterEntity::metadata_count + PatrollingMonsterEntity::hierarchy_metadata_count;

    public:
        RaiderEntity();
        virtual ~RaiderEntity();

        virtual bool IsRaider() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetIsCelebrating() const;

        void SetIsCelebrating(const bool is_celebrating);

    };
}
#endif
