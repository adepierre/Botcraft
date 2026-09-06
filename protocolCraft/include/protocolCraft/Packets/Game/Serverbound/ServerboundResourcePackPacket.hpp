#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundResourcePackPacket : public BasePacket<ServerboundResourcePackPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Resource Pack";

#if PROTOCOL_VERSION < 210 /* < 1.10 */
        SERIALIZED_FIELD(Hash, std::string);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        SERIALIZED_FIELD(Uuid, UUID);
#endif
        SERIALIZED_FIELD(Action, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
