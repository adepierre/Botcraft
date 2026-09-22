#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/GlobalPos.hpp"
#if PROTOCOL_VERSION > 776 /* > 26.2 */
#include "protocolCraft/Types/OptionalVarInt.hpp"
#endif

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
#if PROTOCOL_VERSION < 777 /* < 26.3 */
        SERIALIZED_FIELD(GameType, unsigned char);
        SERIALIZED_FIELD(PreviousGameType, unsigned char);
#else
        SERIALIZED_FIELD(GameType, VarInt);
        SERIALIZED_FIELD(PreviousGameType, OptionalVarInt);
#endif
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
        SERIALIZED_FIELD(LastDeathLocation, std::optional<GlobalPos>);
        SERIALIZED_FIELD(PortalCooldown, VarInt);
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SERIALIZED_FIELD(SeaLevel, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
