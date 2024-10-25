#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/GameProfile/ProfilePublicKey.hpp"

namespace ProtocolCraft
{
    class RemoteChatSessionData : public NetworkType
    {
        SERIALIZED_FIELD(Uuid, UUID);
        SERIALIZED_FIELD(ProfilePublicKey, ProtocolCraft::ProfilePublicKey);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
