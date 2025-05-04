#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundPickItemFromBlockPacket : public BasePacket<ServerboundPickItemFromBlockPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Pick Item From Block";

        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(IncludeData, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
