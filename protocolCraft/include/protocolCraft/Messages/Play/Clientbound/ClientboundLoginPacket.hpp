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
        static constexpr std::string_view packet_name = "Login";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        SERIALIZED_FIELD(PlayerId, int);
        SERIALIZED_FIELD(GameType, unsigned char);
        SERIALIZED_FIELD(Dimension, int);
        SERIALIZED_FIELD(Difficulty, unsigned char);
        SERIALIZED_FIELD(MaxPlayers, unsigned char);
        SERIALIZED_FIELD(LevelType, std::string);
        SERIALIZED_FIELD(ReducedDebugInfo, bool);
#elif PROTOCOL_VERSION < 573 /* < 1.15 */
        SERIALIZED_FIELD(PlayerId, int);
        SERIALIZED_FIELD(GameType, unsigned char);
        SERIALIZED_FIELD(Dimension, int);
        SERIALIZED_FIELD(MaxPlayers, unsigned char);
        SERIALIZED_FIELD(LevelType, std::string);
        SERIALIZED_FIELD(ChunkRadius, VarInt);
        SERIALIZED_FIELD(ReducedDebugInfo, bool);
#elif PROTOCOL_VERSION < 735 /* < 1.16 */
        SERIALIZED_FIELD(PlayerId, int);
        SERIALIZED_FIELD(GameType, unsigned char);
        SERIALIZED_FIELD(Dimension, int);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(MaxPlayers, unsigned char);
        SERIALIZED_FIELD(LevelType, std::string);
        SERIALIZED_FIELD(ChunkRadius, VarInt);
        SERIALIZED_FIELD(ReducedDebugInfo, bool);
        SERIALIZED_FIELD(ShowDeathScreen, bool);
#elif PROTOCOL_VERSION < 751 /* < 1.16.2 */
        SERIALIZED_FIELD(PlayerId, int);
        SERIALIZED_FIELD(GameType, unsigned char);
        SERIALIZED_FIELD(PreviousGameType, unsigned char);
        SERIALIZED_FIELD(Levels, std::vector<Identifier>);
        SERIALIZED_FIELD(RegistryHolder, NBT::UnnamedValue);
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(MaxPlayers, unsigned char);
        SERIALIZED_FIELD(ChunkRadius, VarInt);
        SERIALIZED_FIELD(ReducedDebugInfo, bool);
        SERIALIZED_FIELD(ShowDeathScreen, bool);
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
#elif PROTOCOL_VERSION < 757 /* < 1.18 */
        SERIALIZED_FIELD(PlayerId, int);
        SERIALIZED_FIELD(Hardcore, bool);
        SERIALIZED_FIELD(GameType, unsigned char);
        SERIALIZED_FIELD(PreviousGameType, unsigned char);
        SERIALIZED_FIELD(Levels, std::vector<Identifier>);
        SERIALIZED_FIELD(RegistryHolder, NBT::UnnamedValue);
        SERIALIZED_FIELD(DimensionType, NBT::UnnamedValue);
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(MaxPlayers, VarInt);
        SERIALIZED_FIELD(ChunkRadius, VarInt);
        SERIALIZED_FIELD(ReducedDebugInfo, bool);
        SERIALIZED_FIELD(ShowDeathScreen, bool);
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
#elif PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD(PlayerId, int);
        SERIALIZED_FIELD(Hardcore, bool);
        SERIALIZED_FIELD(GameType, unsigned char);
        SERIALIZED_FIELD(PreviousGameType, unsigned char);
        SERIALIZED_FIELD(Levels, std::vector<Identifier>);
        SERIALIZED_FIELD(RegistryHolder, NBT::UnnamedValue);
        SERIALIZED_FIELD(DimensionType, NBT::UnnamedValue);
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(MaxPlayers, VarInt);
        SERIALIZED_FIELD(ChunkRadius, VarInt);
        SERIALIZED_FIELD(SimulationDistance, VarInt);
        SERIALIZED_FIELD(ReducedDebugInfo, bool);
        SERIALIZED_FIELD(ShowDeathScreen, bool);
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
#elif PROTOCOL_VERSION < 763 /* < 1.20 */
        SERIALIZED_FIELD(PlayerId, int);
        SERIALIZED_FIELD(Hardcore, bool);
        SERIALIZED_FIELD(GameType, unsigned char);
        SERIALIZED_FIELD(PreviousGameType, unsigned char);
        SERIALIZED_FIELD(Levels, std::vector<Identifier>);
        SERIALIZED_FIELD(RegistryHolder, NBT::UnnamedValue);
        SERIALIZED_FIELD(DimensionType, Identifier);
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(MaxPlayers, VarInt);
        SERIALIZED_FIELD(ChunkRadius, VarInt);
        SERIALIZED_FIELD(SimulationDistance, VarInt);
        SERIALIZED_FIELD(ReducedDebugInfo, bool);
        SERIALIZED_FIELD(ShowDeathScreen, bool);
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
        SERIALIZED_FIELD(LastDeathLocation, std::optional<GlobalPos>);
#elif PROTOCOL_VERSION < 764 /* < 1.20.2 */
        SERIALIZED_FIELD(PlayerId, int);
        SERIALIZED_FIELD(Hardcore, bool);
        SERIALIZED_FIELD(GameType, unsigned char);
        SERIALIZED_FIELD(PreviousGameType, unsigned char);
        SERIALIZED_FIELD(Levels, std::vector<Identifier>);
        SERIALIZED_FIELD(RegistryHolder, NBT::UnnamedValue);
        SERIALIZED_FIELD(DimensionType, Identifier);
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(MaxPlayers, VarInt);
        SERIALIZED_FIELD(ChunkRadius, VarInt);
        SERIALIZED_FIELD(SimulationDistance, VarInt);
        SERIALIZED_FIELD(ReducedDebugInfo, bool);
        SERIALIZED_FIELD(ShowDeathScreen, bool);
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
        SERIALIZED_FIELD(LastDeathLocation, std::optional<GlobalPos>);
        SERIALIZED_FIELD(PortalCooldown, VarInt);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(PlayerId, int);
        SERIALIZED_FIELD(Hardcore, bool);
        SERIALIZED_FIELD(Levels, std::vector<Identifier>);
        SERIALIZED_FIELD(MaxPlayers, VarInt);
        SERIALIZED_FIELD(ChunkRadius, VarInt);
        SERIALIZED_FIELD(SimulationDistance, VarInt);
        SERIALIZED_FIELD(ReducedDebugInfo, bool);
        SERIALIZED_FIELD(ShowDeathScreen, bool);
        SERIALIZED_FIELD(DoLimitedCrafting, bool);
        SERIALIZED_FIELD(CommonPlayerSpawnInfo, ProtocolCraft::CommonPlayerSpawnInfo);
#else
        SERIALIZED_FIELD(PlayerId, int);
        SERIALIZED_FIELD(Hardcore, bool);
        SERIALIZED_FIELD(Levels, std::vector<Identifier>);
        SERIALIZED_FIELD(MaxPlayers, VarInt);
        SERIALIZED_FIELD(ChunkRadius, VarInt);
        SERIALIZED_FIELD(SimulationDistance, VarInt);
        SERIALIZED_FIELD(ReducedDebugInfo, bool);
        SERIALIZED_FIELD(ShowDeathScreen, bool);
        SERIALIZED_FIELD(DoLimitedCrafting, bool);
        SERIALIZED_FIELD(CommonPlayerSpawnInfo, ProtocolCraft::CommonPlayerSpawnInfo);
        SERIALIZED_FIELD(EnforceSecureChat, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
