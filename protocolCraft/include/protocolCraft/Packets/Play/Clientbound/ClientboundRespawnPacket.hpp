#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#include "protocolCraft/Types/Identifier.hpp"
#endif
#if PROTOCOL_VERSION > 747 /* > 1.16.1 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Types/NBT/NBT.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
#include "protocolCraft/Types/GlobalPos.hpp"
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Types/CommonPlayerSpawnInfo.hpp"
#endif


namespace ProtocolCraft
{
    class ClientboundRespawnPacket : public BasePacket<ClientboundRespawnPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Respawn";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        SERIALIZED_FIELD(Dimension, int);
        SERIALIZED_FIELD(Difficulty, unsigned char);
        SERIALIZED_FIELD(PlayerGameType, unsigned char);
        SERIALIZED_FIELD(LevelType, std::string);
#elif PROTOCOL_VERSION < 573 /* < 1.15 */
        SERIALIZED_FIELD(Dimension, int);
        SERIALIZED_FIELD(PlayerGameType, unsigned char);
        SERIALIZED_FIELD(LevelType, std::string);
#elif PROTOCOL_VERSION < 735 /* < 1.16 */
        SERIALIZED_FIELD(Dimension, int);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(PlayerGameType, unsigned char);
        SERIALIZED_FIELD(LevelType, std::string);
#elif PROTOCOL_VERSION < 751 /* < 1.16.2 */
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(PlayerGameType, unsigned char);
        SERIALIZED_FIELD(PreviousPlayerGameType, unsigned char);
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
        SERIALIZED_FIELD(KeepAllPlayerData, bool);
#elif PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD(DimensionType, NBT::UnnamedValue);
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(PlayerGameType, unsigned char);
        SERIALIZED_FIELD(PreviousPlayerGameType, unsigned char);
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
        SERIALIZED_FIELD(KeepAllPlayerData, bool);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(DimensionType, Identifier);
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(PlayerGameType, unsigned char);
        SERIALIZED_FIELD(PreviousPlayerGameType, unsigned char);
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
        SERIALIZED_FIELD(KeepAllPlayerData, bool);
        SERIALIZED_FIELD(LastDeathLocation, std::optional<GlobalPos>);
#elif PROTOCOL_VERSION < 763 /* < 1.20 */
        SERIALIZED_FIELD(DimensionType, Identifier);
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(PlayerGameType, unsigned char);
        SERIALIZED_FIELD(PreviousPlayerGameType, unsigned char);
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
        SERIALIZED_FIELD(DataToKeep, unsigned char);
        SERIALIZED_FIELD(LastDeathLocation, std::optional<GlobalPos>);
#elif PROTOCOL_VERSION < 764 /* < 1.20.2 */
        SERIALIZED_FIELD(DimensionType, Identifier);
        SERIALIZED_FIELD(Dimension, Identifier);
        SERIALIZED_FIELD(Seed, long long int);
        SERIALIZED_FIELD(PlayerGameType, unsigned char);
        SERIALIZED_FIELD(PreviousPlayerGameType, unsigned char);
        SERIALIZED_FIELD(IsDebug, bool);
        SERIALIZED_FIELD(IsFlat, bool);
        SERIALIZED_FIELD(DataToKeep, unsigned char);
        SERIALIZED_FIELD(LastDeathLocation, std::optional<GlobalPos>);
        SERIALIZED_FIELD(PortalCooldown, VarInt);
#else
        SERIALIZED_FIELD(CommonPlayerSpawnInfo, ProtocolCraft::CommonPlayerSpawnInfo);
        SERIALIZED_FIELD(DataToKeep, unsigned char);
#endif
        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
