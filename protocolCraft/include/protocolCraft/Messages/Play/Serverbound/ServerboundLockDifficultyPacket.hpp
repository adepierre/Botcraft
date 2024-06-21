#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundLockDifficultyPacket : public BaseMessage<ServerboundLockDifficultyPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Lock Difficulty";

        DECLARE_FIELDS(
            (bool),
            (Locked)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Locked);
    };
} //ProtocolCraft
#endif
