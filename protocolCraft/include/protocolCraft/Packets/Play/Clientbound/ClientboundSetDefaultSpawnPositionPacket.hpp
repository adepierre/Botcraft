#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDefaultSpawnPositionPacket : public BasePacket<ClientboundSetDefaultSpawnPositionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Default Spawn Position";

        SERIALIZED_FIELD(Location, NetworkPosition);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        SERIALIZED_FIELD(Angle, float);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
