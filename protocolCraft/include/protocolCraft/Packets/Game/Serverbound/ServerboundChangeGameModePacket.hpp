#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundChangeGameModePacket : public BasePacket<ServerboundChangeGameModePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Change Game Mode";

        SERIALIZED_FIELD(Mode, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
