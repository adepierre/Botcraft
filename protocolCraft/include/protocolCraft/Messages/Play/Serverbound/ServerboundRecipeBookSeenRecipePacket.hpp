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

        DECLARE_FIELDS(
            (Identifier),
            (Recipe)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Recipe);
    };
} //ProtocolCraft
#endif
