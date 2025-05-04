#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacket : public BasePacket<ServerboundMovePlayerPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Move Player";

        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
