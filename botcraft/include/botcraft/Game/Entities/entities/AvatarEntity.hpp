#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "botcraft/Game/Entities/entities/LivingEntity.hpp"

namespace Botcraft
{
    class AvatarEntity : public LivingEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_player_main_hand"),
            std::string_view("data_player_mode_customisation"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = LivingEntity::metadata_count + LivingEntity::hierarchy_metadata_count;

    public:
        AvatarEntity();
        virtual ~AvatarEntity();

        virtual bool IsAvatar() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
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
