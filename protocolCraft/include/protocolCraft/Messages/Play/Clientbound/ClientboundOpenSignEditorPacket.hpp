#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundOpenSignEditorPacket : public BaseMessage<ClientboundOpenSignEditorPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Open Signe Editor";

#if PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS(
            (NetworkPosition),
            (Pos)
        );
#else
        DECLARE_FIELDS(
            (NetworkPosition, bool),
            (Pos,             IsFrontText)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Pos);
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        GETTER_SETTER(IsFrontText);
#endif
    };
} //ProtocolCraft
