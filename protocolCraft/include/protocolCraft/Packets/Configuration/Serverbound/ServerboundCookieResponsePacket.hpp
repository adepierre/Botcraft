#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <optional>

namespace ProtocolCraft
{
    class ServerboundCookieResponseConfigurationPacket : public BasePacket<ServerboundCookieResponseConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Cookie Response (Configuration)";

        SERIALIZED_FIELD(Key, Identifier);
        SERIALIZED_FIELD(Payload, std::optional<Internal::Vector<unsigned char, void, 0>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
