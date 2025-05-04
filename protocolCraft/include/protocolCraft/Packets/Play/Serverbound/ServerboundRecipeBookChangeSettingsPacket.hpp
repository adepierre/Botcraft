#pragma once

#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundRecipeBookChangeSettingsPacket : public BasePacket<ServerboundRecipeBookChangeSettingsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Recipe Book Change Settings";

        SERIALIZED_FIELD(BookType, VarInt);
        SERIALIZED_FIELD(IsOpen, bool);
        SERIALIZED_FIELD(IsFiltering, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
