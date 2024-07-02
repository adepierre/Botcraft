#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetContentPacket : public BaseMessage<ClientboundContainerSetContentPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Container Set Content";

#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
        DECLARE_FIELDS(
            (unsigned char, Internal::Vector<Slot, short>),
            (ContainerId,   Items)
        );
#else
        DECLARE_FIELDS(
            (unsigned char, VarInt,  std::vector<Slot>, Slot),
            (ContainerId,   StateId, Items,             CarriedItem)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Items);
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        GETTER_SETTER(StateId);
        GETTER_SETTER(CarriedItem);
#endif
    };
} //ProtocolCraft
