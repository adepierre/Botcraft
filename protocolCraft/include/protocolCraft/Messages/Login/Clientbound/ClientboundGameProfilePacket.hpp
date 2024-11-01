#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/GameProfile/GameProfile.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundGameProfilePacket : public BaseMessage<ClientboundGameProfilePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Game Profile";

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        SERIALIZED_FIELD(Uuid, std::string);
        SERIALIZED_FIELD(Username, std::string);
#elif PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD(Uuid, UUID);
        SERIALIZED_FIELD(Username, std::string);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(GameProfile, ProtocolCraft::GameProfile);
#else
        SERIALIZED_FIELD(GameProfile, ProtocolCraft::GameProfile);
        SERIALIZED_FIELD(StrictErrorHandling, bool);
#endif
        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
