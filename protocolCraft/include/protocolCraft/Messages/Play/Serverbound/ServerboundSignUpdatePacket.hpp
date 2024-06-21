#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

#include <array>

namespace ProtocolCraft
{
    class ServerboundSignUpdatePacket : public BaseMessage<ServerboundSignUpdatePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Sign Update";

#if PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS(
            (NetworkPosition, std::array<std::string, 4>),
            (Pos,             Lines)
        );
#else
        DECLARE_FIELDS(
            (NetworkPosition, bool,        std::array<std::string, 4>),
            (Pos,             IsFrontText, Lines)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Pos);
        GETTER_SETTER(Lines);
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        GETTER_SETTER(IsFrontText);
#endif
    };
} //ProtocolCraft
