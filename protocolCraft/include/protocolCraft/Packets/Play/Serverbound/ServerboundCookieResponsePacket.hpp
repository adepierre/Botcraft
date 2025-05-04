#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <optional>
#include <vector>

namespace ProtocolCraft
{
    class ServerboundCookieResponsePacket : public BasePacket<ServerboundCookieResponsePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Cookie Response";

        SERIALIZED_FIELD(Key, Identifier);
        SERIALIZED_FIELD(Payload, std::optional<Internal::Vector<unsigned char, void, 0>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
