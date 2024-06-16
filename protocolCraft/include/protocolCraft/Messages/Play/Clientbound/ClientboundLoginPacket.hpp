#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
#include "protocolCraft/Types/GlobalPos.hpp"
#endif
#include "protocolCraft/Types/NBT/NBT.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Types/CommonPlayerSpawnInfo.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundLoginPacket : public BaseMessage<ClientboundLoginPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */ || PROTOCOL_VERSION == 477 /* 1.14 */ ||  \
      PROTOCOL_VERSION == 480 /* 1.14.1 */ || PROTOCOL_VERSION == 485 /* 1.14.2 */ ||  \
      PROTOCOL_VERSION == 490 /* 1.14.3 */ || PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x2B;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Login";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS_TYPES(int,      unsigned char, int,       unsigned char, unsigned char, std::string, bool);
        DECLARE_FIELDS_NAMES(PlayerId, GameType,      Dimension, Difficulty,    MaxPlayers,    LevelType,   ReducedDebugInfo);
#elif PROTOCOL_VERSION < 573 /* < 1.15 */
        DECLARE_FIELDS_TYPES(int,      unsigned char, int,       unsigned char, std::string, VarInt,      bool);
        DECLARE_FIELDS_NAMES(PlayerId, GameType,      Dimension, MaxPlayers,    LevelType,   ChunkRadius, ReducedDebugInfo);
#elif PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS_TYPES(int,      unsigned char, int,       long long int, unsigned char, std::string, VarInt,      bool,             bool);
        DECLARE_FIELDS_NAMES(PlayerId, GameType,      Dimension, Seed,          MaxPlayers,    LevelType,   ChunkRadius, ReducedDebugInfo, ShowDeathScreen);
#elif PROTOCOL_VERSION < 751 /* < 1.16.2 */
        DECLARE_FIELDS_TYPES(int,      unsigned char, unsigned char,    std::vector<Identifier>, NBT::UnnamedValue, Identifier, long long int, unsigned char, VarInt,      bool,             bool,            bool,    bool);
        DECLARE_FIELDS_NAMES(PlayerId, GameType,      PreviousGameType, Levels,                  RegistryHolder,    Dimension,  Seed,          MaxPlayers,    ChunkRadius, ReducedDebugInfo, ShowDeathScreen, IsDebug, IsFlat);
#elif PROTOCOL_VERSION < 757 /* < 1.18 */
        DECLARE_FIELDS_TYPES(int,      bool,     unsigned char, unsigned char,    std::vector<Identifier>, NBT::UnnamedValue, NBT::UnnamedValue, Identifier, long long int, VarInt,     VarInt,      bool,             bool,            bool,    bool);
        DECLARE_FIELDS_NAMES(PlayerId, Hardcore, GameType,      PreviousGameType, Levels,                  RegistryHolder,    DimensionType,     Dimension,  Seed,          MaxPlayers, ChunkRadius, ReducedDebugInfo, ShowDeathScreen, IsDebug, IsFlat);
#elif PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS_TYPES(int,      bool,     unsigned char, unsigned char,    std::vector<Identifier>, NBT::UnnamedValue, NBT::UnnamedValue, Identifier, long long int, VarInt,     VarInt,      VarInt,             bool,             bool,            bool,    bool);
        DECLARE_FIELDS_NAMES(PlayerId, Hardcore, GameType,      PreviousGameType, Levels,                  RegistryHolder,    DimensionType,     Dimension,  Seed,          MaxPlayers, ChunkRadius, SimulationDistance, ReducedDebugInfo, ShowDeathScreen, IsDebug, IsFlat);
#elif PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS_TYPES(int,      bool,     unsigned char, unsigned char,    std::vector<Identifier>, NBT::UnnamedValue, Identifier,    Identifier, long long int, VarInt,     VarInt,      VarInt,             bool,             bool,            bool,    bool,   std::optional<GlobalPos>);
        DECLARE_FIELDS_NAMES(PlayerId, Hardcore, GameType,      PreviousGameType, Levels,                  RegistryHolder,    DimensionType, Dimension,  Seed,          MaxPlayers, ChunkRadius, SimulationDistance, ReducedDebugInfo, ShowDeathScreen, IsDebug, IsFlat, LastDeathLocation);
#elif PROTOCOL_VERSION < 764 /* < 1.20.2 */
        DECLARE_FIELDS_TYPES(int,      bool,     unsigned char, unsigned char,    std::vector<Identifier>, NBT::UnnamedValue, Identifier,    Identifier, long long int, VarInt,     VarInt,      VarInt,             bool,             bool,            bool,    bool,   std::optional<GlobalPos>, VarInt);
        DECLARE_FIELDS_NAMES(PlayerId, Hardcore, GameType,      PreviousGameType, Levels,                  RegistryHolder,    DimensionType, Dimension,  Seed,          MaxPlayers, ChunkRadius, SimulationDistance, ReducedDebugInfo, ShowDeathScreen, IsDebug, IsFlat, LastDeathLocation,        PortalCooldown);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS_TYPES(int,      bool,     std::vector<Identifier>, VarInt,     VarInt,      VarInt,             bool,             bool,            bool,              CommonPlayerSpawnInfo);
        DECLARE_FIELDS_NAMES(PlayerId, Hardcore, Levels,                  MaxPlayers, ChunkRadius, SimulationDistance, ReducedDebugInfo, ShowDeathScreen, DoLimitedCrafting, CommonPlayerSpawnInfo);
#else
        DECLARE_FIELDS_TYPES(int,      bool,     std::vector<Identifier>, VarInt,     VarInt,      VarInt,             bool,             bool,            bool,              CommonPlayerSpawnInfo, bool);
        DECLARE_FIELDS_NAMES(PlayerId, Hardcore, Levels,                  MaxPlayers, ChunkRadius, SimulationDistance, ReducedDebugInfo, ShowDeathScreen, DoLimitedCrafting, CommonPlayerSpawnInfo, EnforceSecureChat);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(PlayerId);
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(GameType);
        GETTER_SETTER(Dimension);
#endif
        GETTER_SETTER(MaxPlayers);
        GETTER_SETTER(ReducedDebugInfo);
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        GETTER_SETTER(Difficulty);
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        GETTER_SETTER(ChunkRadius);
#endif
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(Seed);
#endif
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        GETTER_SETTER(ShowDeathScreen);
#endif
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(PreviousGameType);
        GETTER_SETTER(RegistryHolder);
#endif
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(IsDebug);
        GETTER_SETTER(IsFlat);
#endif
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        GETTER_SETTER(Levels);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(DimensionType);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        GETTER_SETTER(Hardcore);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        GETTER_SETTER(SimulationDistance);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(LastDeathLocation);
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(PortalCooldown);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        GETTER_SETTER(DoLimitedCrafting);
        GETTER_SETTER(CommonPlayerSpawnInfo);
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        GETTER_SETTER(EnforceSecureChat);
#endif
    };
} //ProtocolCraft
