#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundUseItemOnPacket : public BaseMessage<ServerboundUseItemOnPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Use Item On";

#if PROTOCOL_VERSION > 452 /* > 1.13.2 */
        SERIALIZED_FIELD(Hand, VarInt);
#endif
        SERIALIZED_FIELD(Location, NetworkPosition);
        SERIALIZED_FIELD(Direction, VarInt);
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        SERIALIZED_FIELD(Hand, VarInt);
#endif
        SERIALIZED_FIELD(CursorPositionX, float);
        SERIALIZED_FIELD(CursorPositionY, float);
        SERIALIZED_FIELD(CursorPositionZ, float);
#if PROTOCOL_VERSION > 452 /* > 1.13.2 */
        SERIALIZED_FIELD(Inside, bool);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SERIALIZED_FIELD(WorldBorderHit, bool);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SERIALIZED_FIELD(Sequence, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
