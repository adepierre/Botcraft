#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
#include "protocolCraft/Types/NetworkPosition.hpp"
#else
#include "protocolCraft/Types/LevelDataRespawnData.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSetDefaultSpawnPositionPacket : public BasePacket<ClientboundSetDefaultSpawnPositionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Default Spawn Position";

#if PROTOCOL_VERSION < 773 /* < 1.21.9 */
        SERIALIZED_FIELD(Location, NetworkPosition);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        SERIALIZED_FIELD(Angle, float);
#endif
#else
        SERIALIZED_FIELD(RespawnData, LevelDataRespawnData);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
