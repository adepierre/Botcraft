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
        DECLARE_FIELDS(
            (Identifier,    Identifier, long long int, unsigned char, unsigned char,    bool,    bool,   std::optional<GlobalPos>, VarInt),
            (DimensionType, Dimension,  Seed,          GameType,      PreviousGameType, IsDebug, IsFlat, LastDeathLocation,        PortalCooldown)
        );
#else
        DECLARE_FIELDS(
            (VarInt,        Identifier, long long int, unsigned char, unsigned char,    bool,    bool,   std::optional<GlobalPos>, VarInt),
            (DimensionType, Dimension,  Seed,          GameType,      PreviousGameType, IsDebug, IsFlat, LastDeathLocation,        PortalCooldown)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(DimensionType);
        GETTER_SETTER(Dimension);
        GETTER_SETTER(Seed);
        GETTER_SETTER(GameType);
        GETTER_SETTER(PreviousGameType);
        GETTER_SETTER(IsDebug);
        GETTER_SETTER(IsFlat);
        GETTER_SETTER(LastDeathLocation);
        GETTER_SETTER(PortalCooldown);
    };
}
#endif
