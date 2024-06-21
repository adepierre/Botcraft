#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundUseItemPacket : public BaseMessage<ServerboundUseItemPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Use Item";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (VarInt),
            (Hand)
        );
#elif PROTOCOL_VERSION < 767 /* < 1.21*/
        DECLARE_FIELDS(
            (VarInt, VarInt),
            (Hand,   Sequence)
        );
#else
        DECLARE_FIELDS(
            (VarInt, VarInt,   float, float),
            (Hand,   Sequence, YRot,  XRot)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Hand);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(Sequence);
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        GETTER_SETTER(YRot);
        GETTER_SETTER(XRot);
#endif
    };
} //ProtocolCraft
