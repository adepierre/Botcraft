#pragma once

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/raid/RaiderEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    class AbstractIllagerEntity : public RaiderEntity
#else
    class AbstractIllagerEntity : public MonsterEntity
#endif
    {
#if PROTOCOL_VERSION < 405 /* < 1.14 */
    private:
        static constexpr std::array metadata_names{
            std::string_view("has_target"),
        };
#endif
    protected:
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int hierarchy_metadata_count = RaiderEntity::metadata_count + RaiderEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;
#endif

    public:
        AbstractIllagerEntity();
        virtual ~AbstractIllagerEntity();

        virtual bool IsAbstractIllager() const override;


#if PROTOCOL_VERSION < 405 /* < 1.14 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        char GetHasTarget() const;

        void SetHasTarget(const char has_target);
#endif
    };
}
