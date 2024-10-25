#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundRenameItemPacket : public BaseMessage<ServerboundRenameItemPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Rename Item";

        SERIALIZED_FIELD(Name_, std::string);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
