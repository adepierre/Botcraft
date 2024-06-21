#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundSetStructureBlockPacket : public BaseMessage<ServerboundSetStructureBlockPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Structure Block";

        DECLARE_FIELDS(
            (NetworkPosition, VarInt,     VarInt, std::string, char,    char,    char,    char,  char,  char,  VarInt, VarInt,   std::string, float,     VarLong, char),
            (Pos,             UpdateType, Mode,   Name_,       OffsetX, OffsetY, OffsetZ, SizeX, SizeY, SizeZ, Mirror, Rotation, Data,        Integrity, Seed,    Flags)
        );
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
