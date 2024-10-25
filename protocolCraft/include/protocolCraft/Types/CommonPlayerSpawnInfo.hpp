#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/GlobalPos.hpp"

namespace ProtocolCraft
{
    class CommonPlayerSpawnInfo : public NetworkType
    {
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(DimensionType, Identifier);
#else
        SERIALIZED_FIELD(DimensionType, VarInt);
#endif
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(GameType, unsigned char);
        SERIALIZED_FIELD(PreviousGameType, unsigned char);
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
        SERIALIZED_FIELD(LastDeathLocation, std::optional<GlobalPos>);
        SERIALIZED_FIELD(PortalCooldown, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
