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
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Respawn";

        virtual ~ClientboundRespawnPacket() override
        {

        }

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#if PROTOCOL_VERSION > 729 /* > 1.15.2 */
#if PROTOCOL_VERSION > 747 /* > 1.16.1 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
        void SetDimensionType(const NBT::Value& dimension_type_)
        {
            dimension_type = dimension_type_;
        }
#elif PROTOCOL_VERSION > 758 /* > 1.18.2 */
        void SetDimensionType(const Identifier& dimension_type_)
        {
            dimension_type = dimension_type_;
        }
#endif

        void SetDimension(const Identifier& dimension_)
        {
            dimension = dimension_;
        }
#else
        void SetDimension(const int dimension_)
        {
            dimension = dimension_;
        }
#endif

#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
        void SetSeed(const long long int seed_)
        {
            seed = seed_;
        }
#endif

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        void SetDifficulty(const int difficulty_)
        {
            difficulty = difficulty_;
        }
#endif

        void SetPlayerGameType(const int player_game_type_)
        {
            player_game_type = player_game_type_;
        }

#if PROTOCOL_VERSION < 730 /* < 1.16 */
        void SetLevelType(const std::string& level_type_)
        {
            level_type = level_type_;
        }
#else
        void SetPreviousPlayerGameType(const int previous_player_game_type_)
        {
            previous_player_game_type = previous_player_game_type_;
        }

        void SetIsDebug(const bool is_debug_)
        {
            is_debug = is_debug_;
        }

        void SetIsFlat(const bool is_flat_)
        {
            is_flat = is_flat_;
        }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        void SetKeepAllPlayerData(const bool keep_all_player_data_)
        {
            keep_all_player_data = keep_all_player_data_;
        }
#else
        void SetDataToKeep(const unsigned char data_to_keep_)
        {
            data_to_keep = data_to_keep_;
        }
#endif
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        void SetLastDeathLocation(const std::optional<GlobalPos>& last_death_location_)
        {
            last_death_location = last_death_location_;
        }
#endif

#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        void SetPortalCooldown(const int portal_cooldown_)
        {
            portal_cooldown = portal_cooldown_;
        }
#endif
#else
        void SetCommonPlayerSpawnInfo(const CommonPlayerSpawnInfo& common_player_spawn_info_)
        {
            common_player_spawn_info = common_player_spawn_info_;
        }

        void SetDataToKeep(const unsigned char data_to_keep_)
        {
            data_to_keep = data_to_keep_;
        }
#endif


#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#if PROTOCOL_VERSION > 729 /* > 1.15.2 */
#if PROTOCOL_VERSION > 747 /* > 1.16.1 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
        const NBT::Value& GetDimensionType() const
        {
            return dimension_type;
        }
#elif PROTOCOL_VERSION > 758 /* > 1.18.2 */
        const Identifier& GetDimensionType() const
        {
            return dimension_type;
        }
#endif

        const Identifier& GetDimension() const
        {
            return dimension;
        }
#else
        int GetDimension() const
        {
            return dimension;
        }
#endif

#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
        long long int GetSeed() const
        {
            return seed;
        }
#endif

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        int GetDifficulty() const
        {
            return difficulty;
        }
#endif

        int GetPlayerGameType() const
        {
            return player_game_type;
        }

#if PROTOCOL_VERSION < 730 /* < 1.16 */
        const std::string& GetLevelType() const
        {
            return level_type;
        }
#else
        int GetPreviousPlayerGameType() const
        {
            return previous_player_game_type;
        }

        bool GetIsDebug() const
        {
            return is_debug;
        }

        bool GetIsFlat() const
        {
            return is_flat;
        }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        bool GetKeepAllPlayerData() const
        {
            return keep_all_player_data;
        }
#else
        unsigned char GetDataToKeep() const
        {
            return data_to_keep;
        }
#endif
#endif

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        const std::optional<GlobalPos>& GetLastDeathLocation() const
        {
            return last_death_location;
        }
#endif

#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        int GetPortalCooldown() const
        {
            return portal_cooldown;
        }
#endif
#else
        const CommonPlayerSpawnInfo& GetCommonPlayerSpawnInfo() const
        {
            return common_player_spawn_info;
        }

        unsigned char GetDataToKeep() const
        {
            return data_to_keep;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#if PROTOCOL_VERSION > 729 /* > 1.15.2 */
#if PROTOCOL_VERSION > 747 /* > 1.16.1 */
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            dimension_type = ReadData<NBT::UnnamedValue>(iter, length);
#else
            dimension_type = ReadData<Identifier>(iter, length);
#endif
#endif
            dimension = ReadData<Identifier>(iter, length);
#else
            dimension = ReadData<int>(iter, length);
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
            seed = ReadData<long long int>(iter, length);
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
            difficulty = ReadData<unsigned char>(iter, length);
#endif
            player_game_type = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION < 730 /* < 1.16 */
            level_type = ReadData<std::string>(iter, length);
#else
            previous_player_game_type = ReadData<unsigned char>(iter, length);
            is_debug = ReadData<bool>(iter, length);
            is_flat = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            keep_all_player_data = ReadData<bool>(iter, length);
#else
            data_to_keep = ReadData<unsigned char>(iter, length);
#endif
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            last_death_location = ReadOptional<GlobalPos>(iter, length);
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
            portal_cooldown = ReadData<VarInt>(iter, length);
#endif
#else
            common_player_spawn_info = ReadData<CommonPlayerSpawnInfo>(iter, length);
            data_to_keep = ReadData<unsigned char>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#if PROTOCOL_VERSION > 729 /* > 1.15.2 */
#if PROTOCOL_VERSION > 747 /* > 1.16.1 */
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            WriteData<NBT::UnnamedValue>(dimension_type, container);
#else
            WriteData<Identifier>(dimension_type, container);
#endif
#endif
            WriteData<Identifier>(dimension, container);
#else
            WriteData<int>(dimension, container);
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
            WriteData<long long int>(seed, container);
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
            WriteData<unsigned char>((unsigned char)difficulty, container);
#endif
            WriteData<unsigned char>((unsigned char)player_game_type, container);
#if PROTOCOL_VERSION < 730 /* < 1.16 */
            WriteData<std::string>(level_type, container);
#else
            WriteData<unsigned char>((unsigned char)previous_player_game_type, container);
            WriteData<bool>(is_debug, container);
            WriteData<bool>(is_flat, container);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            WriteData<bool>(keep_all_player_data, container);
#else
            WriteData<unsigned char>(data_to_keep, container);
#endif
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            WriteOptional<GlobalPos>(last_death_location, container);
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
            WriteData<VarInt>(portal_cooldown, container);
#endif
#else
            WriteData<CommonPlayerSpawnInfo>(common_player_spawn_info, container);
            WriteData<unsigned char>(data_to_keep, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#if PROTOCOL_VERSION > 729 /* > 1.15.2 */
#if PROTOCOL_VERSION > 747 /* > 1.16.1 */
            output["dimension_type"] = dimension_type;
#endif
            output["dimension"] = dimension;
#else
            output["dimension"] = dimension;
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
            output["seed"] = seed;
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
            output["difficulty"] = difficulty;
#endif
            output["player_game_type"] = player_game_type;
#if PROTOCOL_VERSION < 730 /* < 1.16 */
            output["level_type"] = level_type;
#else
            output["previous_player_game_type"] = previous_player_game_type;
            output["is_debug"] = is_debug;
            output["is_flat"] = is_flat;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            output["keep_all_player_data"] = keep_all_player_data;
#else
            output["data_to_keep"] = data_to_keep;
#endif
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            if (last_death_location.has_value())
            {
                output["last_death_location"] = last_death_location.value();
            }
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
            output["portal_cooldown"] = portal_cooldown;
#endif
#else
            output["common_player_spawn_info"] = common_player_spawn_info;
            output["data_to_keep"] = data_to_keep;
#endif

            return output;
    }

    private:
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
#if PROTOCOL_VERSION > 729 /* > 1.15.2 */
#if PROTOCOL_VERSION > 747 /* > 1.16.1 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
        NBT::Value dimension_type;
#elif PROTOCOL_VERSION > 758 /* > 1.18.2 */
        Identifier dimension_type;
#endif
        Identifier dimension;
#else
        int dimension = 0;
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
        long long int seed = 0;
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        int difficulty = 0;
#endif
        int player_game_type = 0;
#if PROTOCOL_VERSION < 730 /* < 1.16 */
        std::string level_type;
#else
        int previous_player_game_type = 0;
        bool is_debug = false;
        bool is_flat = false;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        bool keep_all_player_data = false;
#else
        unsigned char data_to_keep = 0;
#endif
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        std::optional<GlobalPos> last_death_location;
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        int portal_cooldown = 0;
#endif
#else
        CommonPlayerSpawnInfo common_player_spawn_info;
        unsigned char data_to_keep = 0;
#endif
    };
} //ProtocolCraft
