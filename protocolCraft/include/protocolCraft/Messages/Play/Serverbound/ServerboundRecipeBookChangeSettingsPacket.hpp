#pragma once

#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundRecipeBookChangeSettingsPacket : public BaseMessage<ServerboundRecipeBookChangeSettingsPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Recipe Book Change Settings";

        DECLARE_FIELDS(
            (VarInt,   bool,   bool),
            (BookType, IsOpen, IsFiltering)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(BookType);
        GETTER_SETTER(IsOpen);
        GETTER_SETTER(IsFiltering);
    };
} //ProtocolCraft
#endif
