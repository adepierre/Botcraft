#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundOpenSignEditorPacket : public BaseMessage<ClientboundOpenSignEditorPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Open Signe Editor";

        SERIALIZED_FIELD(Pos, NetworkPosition);
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        SERIALIZED_FIELD(IsFrontText, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
