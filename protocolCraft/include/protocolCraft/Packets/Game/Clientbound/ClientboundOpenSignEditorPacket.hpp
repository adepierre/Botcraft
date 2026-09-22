#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundOpenSignEditorPacket : public BasePacket<ClientboundOpenSignEditorPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Open Sign Editor";

        SERIALIZED_FIELD(Pos, NetworkPosition);
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */ && PROTOCOL_VERSION < 777 /* < 26.3 */
        SERIALIZED_FIELD(IsFrontText, bool);
#endif
#if PROTOCOL_VERSION > 776 /* > 26.2 */
        SERIALIZED_FIELD(Slot, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
