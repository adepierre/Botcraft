#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHorseScreenOpenPacket : public BaseMessage<ClientboundHorseScreenOpenPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Horse Screen Open";

#if PROTOCOL_VERSION < 767 /* < 1.21 */
        DECLARE_FIELDS(
            (char,        VarInt, int),
            (ContainerId, Size,   EntityId)
        );
#else
        DECLARE_FIELDS(
            (char,        VarInt,           int),
            (ContainerId, InventoryColumns, EntityId)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        GETTER_SETTER(Size);
#else
        GETTER_SETTER(InventoryColumns);
#endif
        GETTER_SETTER(EntityId);
    };
} //ProtocolCraft
#endif
