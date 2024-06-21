#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Types/ChunkPos.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundForgetLevelChunkPacket : public BaseMessage<ClientboundForgetLevelChunkPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Forget Level Chunk";

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        DECLARE_FIELDS(
            (int, int),
            (X,   Z)
        );
#else
        DECLARE_FIELDS(
            (ChunkPos),
            (Pos)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(X);
        GETTER_SETTER(Z);
#else
        GETTER_SETTER(Pos);
#endif
    };
} //ProtocolCraft
