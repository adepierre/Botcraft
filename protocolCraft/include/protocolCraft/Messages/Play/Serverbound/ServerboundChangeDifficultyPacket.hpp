#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChangeDifficultyPacket : public BaseMessage<ServerboundChangeDifficultyPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Change Difficulty";

        DECLARE_FIELDS(
            (char),
            (Difficulty)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Difficulty);
    };
} //ProtocolCraft
#endif
