#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#if PROTOCOL_VERSION < 107 /* < 1.9 */
#include "protocolCraft/Types/Item/Slot.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundUseItemOnPacket : public BasePacket<ServerboundUseItemOnPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Use Item On";

#if PROTOCOL_VERSION > 452 /* > 1.13.2 */
        SERIALIZED_FIELD(Hand, VarInt);
#endif
        SERIALIZED_FIELD(Location, NetworkPosition);
#if PROTOCOL_VERSION < 107 /* < 1.9 */
        SERIALIZED_FIELD(Direction, unsigned char);
        SERIALIZED_FIELD(Item, Slot);
#else
        SERIALIZED_FIELD(Direction, VarInt);
#endif
#if PROTOCOL_VERSION > 47 /* > 1.8.9 */ && PROTOCOL_VERSION < 477 /* < 1.14 */
        SERIALIZED_FIELD(Hand, VarInt);
#endif
#if PROTOCOL_VERSION < 315 /* < 1.11 */
        SERIALIZED_FIELD(CursorPositionX, unsigned char);
        SERIALIZED_FIELD(CursorPositionY, unsigned char);
        SERIALIZED_FIELD(CursorPositionZ, unsigned char);
#else
        SERIALIZED_FIELD(CursorPositionX, float);
        SERIALIZED_FIELD(CursorPositionY, float);
        SERIALIZED_FIELD(CursorPositionZ, float);
#endif
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
