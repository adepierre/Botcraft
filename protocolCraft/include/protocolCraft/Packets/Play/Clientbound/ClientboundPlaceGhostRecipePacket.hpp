#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundPlaceGhostRecipePacket : public BasePacket<ClientboundPlaceGhostRecipePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Place Ghost Recipe";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(ContainerId, char);
#else
        SERIALIZED_FIELD(ContainerId, VarInt);
#endif
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        SERIALIZED_FIELD(Recipe, VarInt);
#elif PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(Recipe, Identifier);
#else
        SERIALIZED_FIELD(RecipeDisplay, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
