#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundResourcePackPacket : public BasePacket<ClientboundResourcePackPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Ressource Pack";

        SERIALIZED_FIELD(Url, std::string);
        SERIALIZED_FIELD(Hash, std::string);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        SERIALIZED_FIELD(Required, bool);
        SERIALIZED_FIELD(Prompt, std::optional<Chat>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
