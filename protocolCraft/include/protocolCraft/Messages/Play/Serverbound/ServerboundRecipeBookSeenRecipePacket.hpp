#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundRecipeBookSeenRecipePacket : public BaseMessage<ServerboundRecipeBookSeenRecipePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Recipe Book Seen Recipe";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(Recipe, Identifier);
#else
        SERIALIZED_FIELD(Recipe, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
