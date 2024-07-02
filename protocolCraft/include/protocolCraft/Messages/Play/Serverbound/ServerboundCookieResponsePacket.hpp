#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <optional>
#include <vector>

namespace ProtocolCraft
{
    class ServerboundCookieResponsePacket : public BaseMessage<ServerboundCookieResponsePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Cookie Response";

        DECLARE_FIELDS(
            (Identifier, std::optional<Internal::Vector<unsigned char, void, 0>>),
            (Key,        Payload)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Key);
        GETTER_SETTER(Payload);
    };
} // ProtocolCraft
#endif
