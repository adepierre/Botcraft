#if PROTOCOL_VERSION > 711 /* > 1.15.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundJigsawGeneratePacket : public BasePacket<ServerboundJigsawGeneratePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Jigsaw Generate";

        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(Levels, VarInt);
        SERIALIZED_FIELD(KeepJigsaws, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
