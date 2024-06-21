#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerButtonClickPacket : public BaseMessage<ServerboundContainerButtonClickPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Container Button Click";

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (char,        char),
            (ContainerId, ButtonId)
        );
#else
        DECLARE_FIELDS(
            (VarInt,      VarInt),
            (ContainerId, ButtonId)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(ButtonId);
    };
} //ProtocolCraft
#endif
