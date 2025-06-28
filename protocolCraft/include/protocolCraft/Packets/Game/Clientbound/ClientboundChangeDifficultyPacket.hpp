#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundChangeDifficultyPacket : public BasePacket<ClientboundChangeDifficultyPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Change Difficulty";

#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
        SERIALIZED_FIELD(Difficulty, unsigned char);
#else
        SERIALIZED_FIELD(Difficulty, VarInt);
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        SERIALIZED_FIELD(Locked, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
