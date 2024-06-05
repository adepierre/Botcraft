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
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x3E;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x41;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x47;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Respawn";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS_TYPES(int,       unsigned char, unsigned char,  std::string);
        DECLARE_FIELDS_NAMES(Dimension, Difficulty,    PlayerGameType, LevelType);
#elif PROTOCOL_VERSION < 573 /* < 1.15 */
        DECLARE_FIELDS_TYPES(int,       unsigned char,  std::string);
        DECLARE_FIELDS_NAMES(Dimension, PlayerGameType, LevelType);
#elif PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS_TYPES(int,       long long int, unsigned char,  std::string);
        DECLARE_FIELDS_NAMES(Dimension, Seed,          PlayerGameType, LevelType);
#elif PROTOCOL_VERSION < 751 /* < 1.16.2 */
        DECLARE_FIELDS_TYPES(Identifier, long long int, unsigned char,  unsigned char,          bool,    bool,   bool);
        DECLARE_FIELDS_NAMES(Dimension,  Seed,          PlayerGameType, PreviousPlayerGameType, IsDebug, IsFlat, KeepAllPlayerData);
#elif PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS_TYPES(NBT::UnnamedValue, Identifier, long long int, unsigned char,  unsigned char,          bool,    bool,   bool);
        DECLARE_FIELDS_NAMES(DimensionType,     Dimension,  Seed,          PlayerGameType, PreviousPlayerGameType, IsDebug, IsFlat, KeepAllPlayerData);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS_TYPES(Identifier,    Identifier, long long int, unsigned char,  unsigned char,          bool,    bool,   bool,              std::optional<GlobalPos>);
        DECLARE_FIELDS_NAMES(DimensionType, Dimension,  Seed,          PlayerGameType, PreviousPlayerGameType, IsDebug, IsFlat, KeepAllPlayerData, LastDeathLocation);
#elif PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS_TYPES(Identifier,    Identifier, long long int, unsigned char,  unsigned char,          bool,    bool,   unsigned char, std::optional<GlobalPos>);
        DECLARE_FIELDS_NAMES(DimensionType, Dimension,  Seed,          PlayerGameType, PreviousPlayerGameType, IsDebug, IsFlat, DataToKeep,    LastDeathLocation);
#elif PROTOCOL_VERSION < 764 /* < 1.20.2 */
        DECLARE_FIELDS_TYPES(Identifier,    Identifier, long long int, unsigned char,  unsigned char,          bool,    bool,   unsigned char, std::optional<GlobalPos>, VarInt);
        DECLARE_FIELDS_NAMES(DimensionType, Dimension,  Seed,          PlayerGameType, PreviousPlayerGameType, IsDebug, IsFlat, DataToKeep,    LastDeathLocation,        PortalCooldown);
#else
        DECLARE_FIELDS_TYPES(CommonPlayerSpawnInfo, unsigned char);
        DECLARE_FIELDS_NAMES(CommonPlayerSpawnInfo, DataToKeep);
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
