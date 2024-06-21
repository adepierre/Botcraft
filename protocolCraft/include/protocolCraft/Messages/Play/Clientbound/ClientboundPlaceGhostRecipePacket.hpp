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

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (char,        VarInt),
            (ContainerId, Recipe)
        );
#else
        DECLARE_FIELDS(
            (char,        Identifier),
            (ContainerId, Recipe)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Recipe);
    };
} //ProtocolCraft
