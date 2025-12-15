#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "botcraft/Game/Entities/entities/LivingEntity.hpp"

namespace Botcraft
{
    class AvatarEntity : public LivingEntity
    {
    protected:
        static constexpr int metadata_count = 2;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = LivingEntity::metadata_count + LivingEntity::hierarchy_metadata_count;

    public:
        AvatarEntity();
        virtual ~AvatarEntity();

        virtual bool IsAvatar() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
        char GetDataPlayerMainHand() const;
#else
        int GetDataPlayerMainHand() const;
#endif
        char GetDataPlayerModeCustomisation() const;

#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
        void SetDataPlayerMainHand(const char data_player_main_hand);
#else
        void SetDataPlayerMainHand(const int data_player_main_hand);
#endif
        void SetDataPlayerModeCustomisation(const char data_player_mode_customisation);

    };
}
#endif
