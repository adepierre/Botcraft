#pragma once

#include "protocolCraft/BaseMessage.hpp"
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
    class ClientboundRespawnPacket : public BaseMessage<ClientboundRespawnPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Respawn";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS(
            (int,       unsigned char, unsigned char,  std::string),
            (Dimension, Difficulty,    PlayerGameType, LevelType)
        );
#elif PROTOCOL_VERSION < 573 /* < 1.15 */
        DECLARE_FIELDS(
            (int,       unsigned char,  std::string),
            (Dimension, PlayerGameType, LevelType)
        );
#elif PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (int,       long long int, unsigned char,  std::string),
            (Dimension, Seed,          PlayerGameType, LevelType)
        );
#elif PROTOCOL_VERSION < 751 /* < 1.16.2 */
        DECLARE_FIELDS(
            (Identifier, long long int, unsigned char,  unsigned char,          bool,    bool,   bool),
            (Dimension,  Seed,          PlayerGameType, PreviousPlayerGameType, IsDebug, IsFlat, KeepAllPlayerData)
        );
#elif PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (NBT::UnnamedValue, Identifier, long long int, unsigned char,  unsigned char,          bool,    bool,   bool),
            (DimensionType,     Dimension,  Seed,          PlayerGameType, PreviousPlayerGameType, IsDebug, IsFlat, KeepAllPlayerData)
        );
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (Identifier,    Identifier, long long int, unsigned char,  unsigned char,          bool,    bool,   bool,              std::optional<GlobalPos>),
            (DimensionType, Dimension,  Seed,          PlayerGameType, PreviousPlayerGameType, IsDebug, IsFlat, KeepAllPlayerData, LastDeathLocation)
        );
#elif PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS(
            (Identifier,    Identifier, long long int, unsigned char,  unsigned char,          bool,    bool,   unsigned char, std::optional<GlobalPos>),
            (DimensionType, Dimension,  Seed,          PlayerGameType, PreviousPlayerGameType, IsDebug, IsFlat, DataToKeep,    LastDeathLocation)
        );
#elif PROTOCOL_VERSION < 764 /* < 1.20.2 */
        DECLARE_FIELDS(
            (Identifier,    Identifier, long long int, unsigned char,  unsigned char,          bool,    bool,   unsigned char, std::optional<GlobalPos>, VarInt),
            (DimensionType, Dimension,  Seed,          PlayerGameType, PreviousPlayerGameType, IsDebug, IsFlat, DataToKeep,    LastDeathLocation,        PortalCooldown)
        );
#else
        DECLARE_FIELDS(
            (CommonPlayerSpawnInfo, unsigned char),
            (CommonPlayerSpawnInfo, DataToKeep)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(Dimension);
        GETTER_SETTER(PlayerGameType);
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        GETTER_SETTER(Difficulty);
#endif
#if PROTOCOL_VERSION < 735 /* < 1.16 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(LevelType);
#endif
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(Seed);
#endif
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(PreviousPlayerGameType);
        GETTER_SETTER(IsDebug);
        GETTER_SETTER(IsFlat);
#endif
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(KeepAllPlayerData);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(DimensionType);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(LastDeathLocation);
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        GETTER_SETTER(DataToKeep);
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(PortalCooldown);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        GETTER_SETTER(CommonPlayerSpawnInfo);
#endif
    };
} //ProtocolCraft
