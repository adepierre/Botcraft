#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundPlaceGhostRecipePacket : public BaseMessage<ClientboundPlaceGhostRecipePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Place Ghost Recipe";

        SERIALIZED_FIELD(ContainerId, char);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        SERIALIZED_FIELD(Recipe, VarInt);
#else
        SERIALIZED_FIELD(Recipe, Identifier);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
