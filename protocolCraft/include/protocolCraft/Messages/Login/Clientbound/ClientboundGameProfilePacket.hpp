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
        static constexpr int packet_id = 0x02;
        static constexpr std::string_view packet_name = "Game Profile";

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (std::string, std::string),
            (Uuid,        Username)
        );
#elif PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (UUID, std::string),
            (Uuid, Username)
        );
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (GameProfile),
            (GameProfile)
        );
#else
        DECLARE_FIELDS(
            (GameProfile, bool),
            (GameProfile, StrictErrorHandling)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        GETTER_SETTER(Uuid);
        GETTER_SETTER(Username);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(GameProfile);
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        GETTER_SETTER(StrictErrorHandling);
#endif
    };
} //ProtocolCraft
