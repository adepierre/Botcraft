#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundLockDifficultyPacket : public BasePacket<ServerboundLockDifficultyPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Lock Difficulty";

        SERIALIZED_FIELD(Locked, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
