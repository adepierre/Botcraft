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
    protected:
#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
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
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataDirection() const;

        void SetDataDirection(const int data_direction);
#endif
    };
}
