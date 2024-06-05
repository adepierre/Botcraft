#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/GameProfile/ProfilePublicKey.hpp"

namespace ProtocolCraft
{
    class RemoteChatSessionData : public NetworkType
    {
        DECLARE_FIELDS_TYPES(UUID, ProfilePublicKey);
        DECLARE_FIELDS_NAMES(Uuid, ProfilePublicKey);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Uuid);
        GETTER_SETTER(ProfilePublicKey);
    };
}
#endif
