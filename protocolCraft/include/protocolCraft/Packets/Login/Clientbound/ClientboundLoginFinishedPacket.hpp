#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/GameProfile/GameProfile.hpp"

namespace ProtocolCraft
{
    class ClientboundLoginFinishedPacket : public BasePacket<ClientboundLoginFinishedPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Login Finished";

        SERIALIZED_FIELD(GameProfile, ProtocolCraft::GameProfile);
#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
        SERIALIZED_FIELD(SessionId, UUID);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
