#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundChangeDifficultyPacket : public BaseMessage<ClientboundChangeDifficultyPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Change Difficulty";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS(
            (unsigned char),
            (Difficulty)
        );
#else
        DECLARE_FIELDS(
            (unsigned char, bool),
            (Difficulty,    Locked)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Difficulty);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        GETTER_SETTER(Locked);
#endif
    };
} //ProtocolCraft
