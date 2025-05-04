#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPushPacket : public BasePacket<ClientboundResourcePackPushPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Ressource Pack Push";

        SERIALIZED_FIELD(Uuid, UUID);
        SERIALIZED_FIELD(Url, std::string);
        SERIALIZED_FIELD(Hash, std::string);
        SERIALIZED_FIELD(Required, bool);
        SERIALIZED_FIELD(Prompt, std::optional<Chat>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
