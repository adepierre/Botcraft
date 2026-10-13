#pragma once

#if PROTOCOL_VERSION < 767 /* < 1.21 */
#include "botcraft/Game/Entities/entities/Entity.hpp"
#else
#include "botcraft/Game/Entities/entities/decoration/BlockAttachedEntity.hpp"
#endif

namespace Botcraft
{
    class HangingEntity :
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        public Entity
#else
        public BlockAttachedEntity
#endif
    {
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_direction"),
        };
#endif
    protected:
#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
#endif
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = BlockAttachedEntity::metadata_count + BlockAttachedEntity::hierarchy_metadata_count;
#endif

    public:
        HangingEntity();
        virtual ~HangingEntity();

        virtual bool IsHangingEntity() const override;

#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataDirection() const;

        void SetDataDirection(const int data_direction);
#endif
    };
}
