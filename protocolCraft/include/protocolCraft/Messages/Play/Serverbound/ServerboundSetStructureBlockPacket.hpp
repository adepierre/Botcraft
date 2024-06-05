#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundSetStructureBlockPacket : public BaseMessage<ServerboundSetStructureBlockPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */ || PROTOCOL_VERSION == 761 /* 1.19.3 */ ||  \
      PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x34;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Structure Block";

        DECLARE_FIELDS_TYPES(NetworkPosition, VarInt,     VarInt, std::string, char,    char,    char,    char,  char,  char,  VarInt, VarInt,   std::string, float,     VarLong, char);
        DECLARE_FIELDS_NAMES(Pos,             UpdateType, Mode,   Name_,       OffsetX, OffsetY, OffsetZ, SizeX, SizeY, SizeZ, Mirror, Rotation, Data,        Integrity, Seed,    Flags);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Pos);
        GETTER_SETTER(UpdateType);
        GETTER_SETTER(Mode);
        GETTER_SETTER(Name_);
        GETTER_SETTER(OffsetX);
        GETTER_SETTER(OffsetY);
        GETTER_SETTER(OffsetZ);
        GETTER_SETTER(SizeX);
        GETTER_SETTER(SizeY);
        GETTER_SETTER(SizeZ);
        GETTER_SETTER(Mirror);
        GETTER_SETTER(Rotation);
        GETTER_SETTER(Data);
        GETTER_SETTER(Integrity);
        GETTER_SETTER(Seed);
        GETTER_SETTER(Flags);
    };
} //ProtocolCraft
#endif
