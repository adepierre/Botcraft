#if PROTOCOL_VERSION > 711 /* > 1.15.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundJigsawGeneratePacket : public BaseMessage<ServerboundJigsawGeneratePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Jigsaw Generate";

        DECLARE_FIELDS(
            (NetworkPosition, VarInt, bool),
            (Pos,             Levels, KeepJigsaws)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Pos);
        GETTER_SETTER(Levels);
        GETTER_SETTER(KeepJigsaws);
    };
} //ProtocolCraft
#endif
