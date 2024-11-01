#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/GameProfile/GameProfile.hpp"

namespace ProtocolCraft
{
    class ClientboundLoginFinishedPacket : public BaseMessage<ClientboundLoginFinishedPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Login Finished";

        SERIALIZED_FIELD(GameProfile, ProtocolCraft::GameProfile);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
