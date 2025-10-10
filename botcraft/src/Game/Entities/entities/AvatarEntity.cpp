#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "botcraft/Game/Entities/entities/AvatarEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, AvatarEntity::metadata_count> AvatarEntity::metadata_names{ {
        "data_player_main_hand",
        "data_player_mode_customisation",
    } };

    AvatarEntity::AvatarEntity()
    {
        // Initialize all metadata with default values
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


    void AvatarEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            LivingEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }


    char AvatarEntity::GetDataPlayerMainHand() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_player_main_hand"));
    }

    char AvatarEntity::GetDataPlayerModeCustomisation() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_player_mode_customisation"));
    }


    void AvatarEntity::SetDataPlayerMainHand(const char data_player_main_hand)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_player_main_hand"] = data_player_main_hand;
    }

    void AvatarEntity::SetDataPlayerModeCustomisation(const char data_player_mode_customisation)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_player_mode_customisation"] = data_player_mode_customisation;
    }

}
#endif
