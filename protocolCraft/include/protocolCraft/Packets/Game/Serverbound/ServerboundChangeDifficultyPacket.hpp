#if PROTOCOL_VERSION > 463 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundChangeDifficultyPacket : public BasePacket<ServerboundChangeDifficultyPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Change Difficulty";

#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
        SERIALIZED_FIELD(Difficulty, unsigned char);
#else
        SERIALIZED_FIELD(Difficulty, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
