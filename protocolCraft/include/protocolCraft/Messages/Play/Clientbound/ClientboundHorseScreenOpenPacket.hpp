#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHorseScreenOpenPacket : public BaseMessage<ClientboundHorseScreenOpenPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Horse Screen Open";

        SERIALIZED_FIELD(ContainerId, char);
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        SERIALIZED_FIELD(Size, VarInt);
#else
        SERIALIZED_FIELD(InventoryColumns, VarInt);
#endif
        SERIALIZED_FIELD(EntityId, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
