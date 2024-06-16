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
#if   PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x41;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x47;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x49;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x4B;
#else
#error "Protocol version not implemented"
#endif

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
