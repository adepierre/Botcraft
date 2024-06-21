#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundUseItemOnPacket : public BaseMessage<ServerboundUseItemOnPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Use Item On";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS(
            (NetworkPosition, VarInt,    VarInt, float,           float,           float),
            (Location,        Direction, Hand,   CursorPositionX, CursorPositionY, CursorPositionZ)
        );
#elif PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (VarInt, NetworkPosition, VarInt,    float,           float,           float,           bool),
            (Hand,   Location,        Direction, CursorPositionX, CursorPositionY, CursorPositionZ, Inside)
        );
#else
        DECLARE_FIELDS(
            (VarInt, NetworkPosition, VarInt,    float,           float,           float,           bool,   VarInt),
            (Hand,   Location,        Direction, CursorPositionX, CursorPositionY, CursorPositionZ, Inside, Sequence)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Location);
        GETTER_SETTER(Direction);
        GETTER_SETTER(Hand);
        GETTER_SETTER(CursorPositionX);
        GETTER_SETTER(CursorPositionY);
        GETTER_SETTER(CursorPositionZ);
#if PROTOCOL_VERSION > 452 /* > 1.13.2 */
        GETTER_SETTER(Inside);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(Sequence);
#endif
    };
} //ProtocolCraft
