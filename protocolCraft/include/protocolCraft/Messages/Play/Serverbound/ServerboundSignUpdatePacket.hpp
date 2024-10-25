#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

#include <array>

namespace ProtocolCraft
{
    class ServerboundSignUpdatePacket : public BaseMessage<ServerboundSignUpdatePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Sign Update";

        SERIALIZED_FIELD(Pos, NetworkPosition);
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        SERIALIZED_FIELD(IsFrontText, bool);
#endif
        SERIALIZED_FIELD(Lines, std::array<std::string, 4>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
