#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include <string>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundServerDataPacket : public BaseMessage<ClientboundServerDataPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Server Data";

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        DECLARE_FIELDS(
            (std::optional<Chat>, std::optional<std::string>, bool),
            (Motd,                IconBase64,                 PreviewsChat)
        );
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (std::optional<Chat>, std::optional<std::string>, bool,         bool),
            (Motd,                IconBase64,                 PreviewsChat, EnforcesSecureChat)
        );
#elif PROTOCOL_VERSION < 762 /* < 1.19.4 */
        DECLARE_FIELDS(
            (std::optional<Chat>, std::optional<std::string>, bool),
            (Motd,                IconBase64,                 EnforcesSecureChat)
        );
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (Chat, std::optional<std::vector<unsigned char>>, bool),
            (Motd, IconBytes,                                 EnforcesSecureChat)
        );
#else
        DECLARE_FIELDS(
            (Chat, std::optional<std::vector<unsigned char>>),
            (Motd, IconBytes)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Motd);
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        GETTER_SETTER(IconBase64);
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(PreviewsChat);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(EnforcesSecureChat);
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        GETTER_SETTER(IconBytes);
#endif
    };
} //ProtocolCraft
#endif
