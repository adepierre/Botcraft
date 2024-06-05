#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPushPacket : public BaseMessage<ClientboundResourcePackPushPacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x46;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Ressource Pack Push";

        DECLARE_FIELDS_TYPES(UUID, std::string, std::string, bool,     std::optional<Chat>);
        DECLARE_FIELDS_NAMES(Uuid, Url,         Hash,        Required, Prompt);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Uuid);
        GETTER_SETTER(Url);
        GETTER_SETTER(Hash);
        GETTER_SETTER(Required);
        GETTER_SETTER(Prompt);
    };
} //ProtocolCraft
#endif
