#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDefaultSpawnPositionPacket : public BaseMessage<ClientboundSetDefaultSpawnPositionPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Default Spawn Position";

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (NetworkPosition),
            (Location)
        );
#else
        DECLARE_FIELDS(
            (NetworkPosition, float),
            (Location,        Angle)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Location);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        GETTER_SETTER(Angle);
#endif
    };
} //ProtocolCraft
