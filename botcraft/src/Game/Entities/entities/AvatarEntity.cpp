#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "botcraft/Game/Entities/entities/AvatarEntity.hpp"

namespace Botcraft
{
    AvatarEntity::AvatarEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataPlayerMainHand(0);
        SetDataPlayerModeCustomisation(0);
    }

    AvatarEntity::~AvatarEntity()
    {

    }

    bool AvatarEntity::IsAvatar() const
    {
        return true;
    }



    ProtocolCraft::Json::Value AvatarEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = LivingEntity::Serialize();

        output["metadata"]["data_player_main_hand"] = GetDataPlayerMainHand();
        output["metadata"]["data_player_mode_customisation"] = GetDataPlayerModeCustomisation();

        return output;
    }


#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
    char AvatarEntity::GetDataPlayerMainHand() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_main_hand"));
    }
#else
    int AvatarEntity::GetDataPlayerMainHand() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_main_hand"));
    }
#endif

    char AvatarEntity::GetDataPlayerModeCustomisation() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_mode_customisation"));
    }


#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
    void AvatarEntity::SetDataPlayerMainHand(const char data_player_main_hand)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_main_hand"), data_player_main_hand);
    }
#else
    void AvatarEntity::SetDataPlayerMainHand(const int data_player_main_hand)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_main_hand"), data_player_main_hand);
    }
#endif

    void AvatarEntity::SetDataPlayerModeCustomisation(const char data_player_mode_customisation)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_player_mode_customisation"), data_player_mode_customisation);
    }

}
#endif
