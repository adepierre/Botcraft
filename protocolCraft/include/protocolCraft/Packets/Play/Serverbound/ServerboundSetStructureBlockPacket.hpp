#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundSetStructureBlockPacket : public BasePacket<ServerboundSetStructureBlockPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Structure Block";

        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(UpdateType, VarInt);
        SERIALIZED_FIELD(Mode, VarInt);
        SERIALIZED_FIELD(Name_, std::string);
        SERIALIZED_FIELD(OffsetX, char);
        SERIALIZED_FIELD(OffsetY, char);
        SERIALIZED_FIELD(OffsetZ, char);
        SERIALIZED_FIELD(SizeX, char);
        SERIALIZED_FIELD(SizeY, char);
        SERIALIZED_FIELD(SizeZ, char);
        SERIALIZED_FIELD(Mirror, VarInt);
        SERIALIZED_FIELD(Rotation, VarInt);
        SERIALIZED_FIELD(Data, std::string);
        SERIALIZED_FIELD(Integrity, float);
        SERIALIZED_FIELD(Seed, VarLong);
        SERIALIZED_FIELD(Flags, char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
