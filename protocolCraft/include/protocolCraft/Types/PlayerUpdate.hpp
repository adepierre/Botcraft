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
        SERIALIZED_FIELD(Name, std::string);
        SERIALIZED_FIELD(Properties, std::vector<GameProfileProperty>);
        SERIALIZED_FIELD(GameMode, VarInt);
        SERIALIZED_FIELD(Latency, VarInt);
        SERIALIZED_FIELD(DisplayName, std::optional<Chat>);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SERIALIZED_FIELD(ProfilePublicKey, std::optional<ProtocolCraft::ProfilePublicKey>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
