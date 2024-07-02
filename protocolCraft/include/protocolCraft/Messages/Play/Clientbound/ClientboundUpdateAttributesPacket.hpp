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

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (VarInt,   Internal::Vector<EntityProperty, int>),
            (EntityId, Attributes)
        );
#else
        DECLARE_FIELDS(
            (VarInt,   std::vector<EntityProperty>),
            (EntityId, Attributes)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(Attributes);
    };
} //ProtocolCraft
