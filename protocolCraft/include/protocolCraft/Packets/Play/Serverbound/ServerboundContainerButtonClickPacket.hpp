#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerButtonClickPacket : public BasePacket<ServerboundContainerButtonClickPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Button Click";

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(ContainerId, char);
        SERIALIZED_FIELD(ButtonId, char);
#else
        SERIALIZED_FIELD(ContainerId, VarInt);
        SERIALIZED_FIELD(ButtonId, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
