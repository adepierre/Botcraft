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
        DECLARE_FIELDS_TYPES(Identifier,    Identifier, long long int, unsigned char, unsigned char,    bool,    bool,   std::optional<GlobalPos>, VarInt);
#else
        DECLARE_FIELDS_TYPES(VarInt,        Identifier, long long int, unsigned char, unsigned char,    bool,    bool,   std::optional<GlobalPos>, VarInt);
#endif
        DECLARE_FIELDS_NAMES(DimensionType, Dimension,  Seed,          GameType,      PreviousGameType, IsDebug, IsFlat, LastDeathLocation,        PortalCooldown);
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
