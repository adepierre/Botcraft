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
        DECLARE_FIELDS(
            (int,    int,    std::vector<Record>),
            (ChunkX, ChunkZ, Records)
        );
#elif PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS(
            (long long int, bool,                 std::vector<VarLong>),
            (SectionPos,    SuppressLightUpdates, PosState)
        );
#else
        DECLARE_FIELDS(
            (long long int, std::vector<VarLong>),
            (SectionPos,    PosState)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 751 /* < 1.16.2 */
        GETTER_SETTER(ChunkX);
        GETTER_SETTER(ChunkZ);
        GETTER_SETTER(Records);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        GETTER_SETTER(SectionPos);
        GETTER_SETTER(PosState);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
        GETTER_SETTER(SuppressLightUpdates);
#endif
    };
}
