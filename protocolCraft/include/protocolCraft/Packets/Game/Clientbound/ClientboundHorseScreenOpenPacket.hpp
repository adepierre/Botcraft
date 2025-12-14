#if PROTOCOL_VERSION > 451 /* > 1.13.2 */ && PROTOCOL_VERSION < 774 /* < 1.21.11 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundHorseScreenOpenPacket : public BasePacket<ClientboundHorseScreenOpenPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Horse Screen Open";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(ContainerId, char);
#else
        SERIALIZED_FIELD(ContainerId, VarInt);
#endif
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
