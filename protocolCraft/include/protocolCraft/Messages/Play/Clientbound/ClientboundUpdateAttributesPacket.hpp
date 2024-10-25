#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/EntityProperty.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateAttributesPacket : public BaseMessage<ClientboundUpdateAttributesPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Update Attributes";

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        SERIALIZED_FIELD(Attributes, Internal::Vector<EntityProperty, int>);
#else
        SERIALIZED_FIELD(Attributes, std::vector<EntityProperty>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
