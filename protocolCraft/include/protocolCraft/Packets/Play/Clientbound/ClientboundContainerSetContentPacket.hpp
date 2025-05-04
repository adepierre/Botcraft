#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetContentPacket : public BasePacket<ClientboundContainerSetContentPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Set Content";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(ContainerId, unsigned char);
#else
        SERIALIZED_FIELD(ContainerId, VarInt);
#endif
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
