#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/GameProfile/ProfilePublicKey.hpp"
#endif

namespace ProtocolCraft
{
    class PlayerUpdate : public NetworkType
    {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS_TYPES(std::string, std::vector<GameProfileProperty>, VarInt,   VarInt,  std::optional<Chat>);
        DECLARE_FIELDS_NAMES(Name,        Properties,                       GameMode, Latency, DisplayName);
#else
        DECLARE_FIELDS_TYPES(std::string, std::vector<GameProfileProperty>, VarInt,   VarInt,  std::optional<Chat>, std::optional<ProfilePublicKey>);
        DECLARE_FIELDS_NAMES(Name,        Properties,                       GameMode, Latency, DisplayName, ProfilePublicKey);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Name);
        GETTER_SETTER(Properties);
        GETTER_SETTER(GameMode);
        GETTER_SETTER(Latency);
        GETTER_SETTER(DisplayName);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(ProfilePublicKey);
#endif
    };
} // ProtocolCraft
#endif
