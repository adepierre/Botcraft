#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetContentPacket : public BaseMessage<ClientboundContainerSetContentPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Set Content";

        SERIALIZED_FIELD(ContainerId, unsigned char);
#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
        SERIALIZED_FIELD(Items, Internal::Vector<Slot, short>);
#else
        SERIALIZED_FIELD(StateId, VarInt);
        SERIALIZED_FIELD(Items, std::vector<Slot>);
        SERIALIZED_FIELD(CarriedItem, Slot);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
