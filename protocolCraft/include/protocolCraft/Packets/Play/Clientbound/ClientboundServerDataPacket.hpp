#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include <string>

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundServerDataPacket : public BasePacket<ClientboundServerDataPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Server Data";

#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        SERIALIZED_FIELD(Motd, std::optional<Chat>);
#else
        SERIALIZED_FIELD(Motd, Chat);
#endif
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        SERIALIZED_FIELD(IconBase64, std::optional<std::string>);
#else
        SERIALIZED_FIELD(IconBytes, std::optional<std::vector<unsigned char>>);
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(PreviewsChat, bool);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(EnforcesSecureChat, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
