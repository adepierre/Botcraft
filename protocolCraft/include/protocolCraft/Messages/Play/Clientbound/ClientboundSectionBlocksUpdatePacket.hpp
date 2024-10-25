#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
#include "protocolCraft/Types/Record.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSectionBlocksUpdatePacket : public BaseMessage<ClientboundSectionBlocksUpdatePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Section Blocks Update";

#if PROTOCOL_VERSION < 751 /* < 1.16.2 */
        SERIALIZED_FIELD(ChunkX, int);
        SERIALIZED_FIELD(ChunkZ, int);
        SERIALIZED_FIELD(Records, std::vector<Record>);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        SERIALIZED_FIELD(SectionPos, long long int);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
        SERIALIZED_FIELD(SuppressLightUpdates, bool);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        SERIALIZED_FIELD(PosState, std::vector<VarLong>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
