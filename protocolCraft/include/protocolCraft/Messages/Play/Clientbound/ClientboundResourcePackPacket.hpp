#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundResourcePackPacket : public BaseMessage<ClientboundResourcePackPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Ressource Pack";

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (std::string, std::string),
            (Url,         Hash)
        );
#else
        DECLARE_FIELDS(
            (std::string, std::string, bool,     std::optional<Chat>),
            (Url,         Hash,        Required, Prompt)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Url);
        GETTER_SETTER(Hash);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        GETTER_SETTER(Required);
        GETTER_SETTER(Prompt);
#endif
    };
} //ProtocolCraft
#endif
