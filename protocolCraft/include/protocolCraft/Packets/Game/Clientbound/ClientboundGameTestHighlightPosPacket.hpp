#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundGameTestHighlightPosPacket : public BasePacket<ClientboundGameTestHighlightPosPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Test highlight Pos";

        SERIALIZED_FIELD(AbsolutePos, NetworkPosition);
        SERIALIZED_FIELD(RelativePos, NetworkPosition);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
