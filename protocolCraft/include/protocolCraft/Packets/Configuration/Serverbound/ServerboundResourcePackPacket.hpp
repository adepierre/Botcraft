#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundResourcePackConfigurationPacket : public BasePacket<ServerboundResourcePackConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Resource Pack (Configuration)";

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        SERIALIZED_FIELD(Uuid, UUID);
#endif
        SERIALIZED_FIELD(Action, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
