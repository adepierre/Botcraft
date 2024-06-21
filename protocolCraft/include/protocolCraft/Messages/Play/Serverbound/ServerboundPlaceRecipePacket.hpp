#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundPlaceRecipePacket : public BaseMessage<ServerboundPlaceRecipePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Place Recipe";

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (char,        VarInt, bool),
            (ContainerId, Recipe, ShiftDown)
        );
#else
        DECLARE_FIELDS(
            (char,        Identifier, bool),
            (ContainerId, Recipe,     ShiftDown)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Recipe);
        GETTER_SETTER(ShiftDown);
    };
} //ProtocolCraft
