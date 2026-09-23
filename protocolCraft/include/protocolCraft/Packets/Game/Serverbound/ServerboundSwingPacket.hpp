#if PROTOCOL_VERSION < 777 /* < 26.3 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundSwingPacket : public BasePacket<ServerboundSwingPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Swing";

#if PROTOCOL_VERSION > 47 /* > 1.8.9 */
        SERIALIZED_FIELD(Hand, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
