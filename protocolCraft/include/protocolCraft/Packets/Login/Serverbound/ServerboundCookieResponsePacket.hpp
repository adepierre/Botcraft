#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <optional>

namespace ProtocolCraft
{
    class ServerboundCookieResponseLoginPacket : public BasePacket<ServerboundCookieResponseLoginPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Cookie Response (Login)";

        SERIALIZED_FIELD(Key, Identifier);
        SERIALIZED_FIELD(Payload, std::optional<Internal::Vector<unsigned char, void, 0>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
