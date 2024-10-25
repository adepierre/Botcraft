#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundUseItemPacket : public BaseMessage<ServerboundUseItemPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Use Item";

        SERIALIZED_FIELD(Hand, VarInt);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SERIALIZED_FIELD(Sequence, VarInt);
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        SERIALIZED_FIELD(YRot, float);
        SERIALIZED_FIELD(XRot, float);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
