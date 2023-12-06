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
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x29;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Login";

        virtual ~ClientboundLoginPacket() override
        {

        }

        void SetPlayerId(const int player_id_)
        {
            player_id = player_id_;
        }

#if PROTOCOL_VERSION > 551 /* > 1.14.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetSeed(const long long int seed_)
        {
            seed = seed_;
        }
#endif

#if PROTOCOL_VERSION > 737 /* > 1.16.1 */
        void SetHardcore(const bool hardcore_)
        {
            hardcore = hardcore_;
        }
#endif

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetGameType(const unsigned char game_type_)
        {
            game_type = game_type_;
        }
#endif

#if PROTOCOL_VERSION > 718 /* > 1.15.2 */
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetPreviousGameType(const unsigned char previous_game_type_)
        {
            previous_game_type = previous_game_type_;
        }
#endif

        void SetLevels(const std::vector<Identifier>& levels_)
        {
            levels = levels_;
        }

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetRegistryHolder(const NBT::Value& registry_holder_)
        {
            registry_holder = registry_holder_;
        }
#endif

#if PROTOCOL_VERSION > 747 /* > 1.16.1 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
        void SetDimensionType(const NBT::Value& dimension_type_)
        {
            dimension_type = dimension_type_;
        }
#elif PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetDimensionType(const Identifier& dimension_type_)
        {
            dimension_type = dimension_type_;
        }
#endif

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetDimension(const Identifier& dimension_)
        {
            dimension = dimension_;
        }
#endif
#else
        void SetDimension(const int dimension_)
        {
            dimension = dimension_;
        }
#endif

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        void SetDifficulty(const unsigned char difficulty_)
        {
            difficulty = difficulty_;
        }
#endif

#if PROTOCOL_VERSION < 749 /* < 1.16.2 */
        void SetMaxPlayers(const unsigned char max_players_)
        {
            max_players = max_players_;
        }
#else
        void SetMaxPlayers(const int max_players_)
        {
            max_players = max_players_;
        }
#endif

#if PROTOCOL_VERSION < 719 /* < 1.16 */
        void SetLevelType(const std::string& level_type_)
        {
            level_type = level_type_;
        }
#endif

#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
        void SetChunkRadius(const int chunk_radius_)
        {
            chunk_radius = chunk_radius_;
        }
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        void SetSimulationDistance(const int simulation_distance_)
        {
            simulation_distance = simulation_distance_;
        }
#endif

        void SetReducedDebugInfo(const bool reduced_debug_info_)
        {
            reduced_debug_info = reduced_debug_info_;
        }

#if PROTOCOL_VERSION > 565 /* > 1.14.4 */
        void SetShowDeathScreen(const bool show_death_screen_)
        {
            show_death_screen = show_death_screen_;
        }
#endif

#if PROTOCOL_VERSION > 718 /* > 1.15.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetIsDebug(const bool is_debug_)
        {
            is_debug = is_debug_;
        }

        void SetIsFlat(const bool is_flat_)
        {
            is_flat = is_flat_;
        }
#endif

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetLastDeathLocation(const std::optional<GlobalPos>& last_death_location_)
        {
            last_death_location = last_death_location_;
        }
#endif

#if PROTOCOL_VERSION > 762 /* > 1.19.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetPortalCooldown(const int portal_cooldown_)
        {
            portal_cooldown = portal_cooldown_;
        }
#endif

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        void SetDoLimitedCrafting(const bool do_limited_crafting_)
        {
            do_limited_crafting = do_limited_crafting_;
        }

        void SetCommonPlayerSpawnInfo(const CommonPlayerSpawnInfo& common_player_spawn_info_)
        {
            common_player_spawn_info = common_player_spawn_info_;
        }
#endif


        int GetPlayerId() const
        {
            return player_id;
        }

#if PROTOCOL_VERSION > 551 /* > 1.14.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        long long int GetSeed() const
        {
            return seed;
        }
#endif

#if PROTOCOL_VERSION > 737 /* > 1.16.1 */
        bool GetHardcore() const
        {
            return hardcore;
        }
#endif

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        unsigned char GetGameType() const
        {
            return game_type;
        }
#endif

#if PROTOCOL_VERSION > 718 /* > 1.15.2 */
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        unsigned char GetPreviousGameType() const
        {
            return previous_game_type;
        }
#endif

        const std::vector<Identifier>& GetLevels() const
        {
            return levels;
        }

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        const NBT::Value& GetRegistryHolder() const
        {
            return registry_holder;
        }
#endif

#if PROTOCOL_VERSION > 747 /* > 1.16.1 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
        const NBT::Value& GetDimensionType() const
        {
            return dimension_type;
        }
#elif PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        const Identifier& GetDimensionType() const
        {
            return dimension_type;
        }
#endif

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        const Identifier& GetDimension() const
        {
            return dimension;
        }
#endif
#else
        int GetDimension() const
        {
            return dimension;
        }
#endif

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        unsigned char GetDifficulty() const
        {
            return difficulty;
        }
#endif

#if PROTOCOL_VERSION < 749 /* < 1.16.2 */
        unsigned char GetMaxPlayers() const
        {
            return max_players;
        }
#else
        int GetMaxPlayers() const
        {
            return max_players;
        }
#endif

#if PROTOCOL_VERSION < 719 /* < 1.16 */
        const std::string& GetLevelType() const
        {
            return level_type;
        }
#endif

#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
        int GetChunkRadius() const
        {
            return chunk_radius;
        }
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        int GetSimulationDistance() const
        {
            return simulation_distance;
        }
#endif

        bool GetReducedDebugInfo() const
        {
            return reduced_debug_info;
        }

#if PROTOCOL_VERSION > 565 /* > 1.14.4 */
        bool GetShowDeathScreen() const
        {
            return show_death_screen;
        }
#endif
#if PROTOCOL_VERSION > 718 /* > 1.15.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        bool GetIsDebug() const
        {
            return is_debug;
        }

        bool GetIsFlat() const
        {
            return is_flat;
        }
#endif

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        const std::optional<GlobalPos>& GetLastDeathLocation() const
        {
            return last_death_location;
        }
#endif

#if PROTOCOL_VERSION > 762 /* > 1.19.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        int GetPortalCooldown() const
        {
            return portal_cooldown;
        }
#endif

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        bool GetDoLimitedCrafting() const
        {
            return do_limited_crafting;
        }

        const CommonPlayerSpawnInfo& GetCommonPlayerSpanwInfo() const
        {
            return common_player_spawn_info;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            player_id = ReadData<int>(iter, length);
#if PROTOCOL_VERSION > 737 /* > 1.16.1 */
            hardcore = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            game_type = ReadData<unsigned char>(iter, length);
#endif
#if PROTOCOL_VERSION > 718 /* > 1.15.2 */
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            previous_game_type = ReadData<unsigned char>(iter, length);
#endif
            levels = ReadVector<Identifier>(iter, length);
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            registry_holder = ReadData<NBT::UnnamedValue>(iter, length);
#endif

#if PROTOCOL_VERSION > 747 /* > 1.16.1 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
            dimension_type = ReadData<NBT::UnnamedValue>(iter, length);
#elif PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            dimension_type = ReadData<Identifier>(iter, length);
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            dimension = ReadData<Identifier>(iter, length);
#endif
#else
            dimension = ReadData<int>(iter, length);
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            seed = ReadData<long long int>(iter, length);
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
            difficulty = ReadData<unsigned char>(iter, length);
#endif
#if PROTOCOL_VERSION < 749 /* < 1.16.2 */
            max_players = ReadData<unsigned char>(iter, length);
#else
            max_players = ReadData<VarInt>(iter, length);
#endif
#if PROTOCOL_VERSION < 719 /* < 1.16 */
            level_type = ReadData<std::string>(iter, length);
#endif
#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
            chunk_radius = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
            simulation_distance = ReadData<VarInt>(iter, length);
#endif
#endif
            reduced_debug_info = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 565 /* > 1.14.4 */
            show_death_screen = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 718 /* > 1.15.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            is_debug = ReadData<bool>(iter, length);
            is_flat = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            last_death_location = ReadOptional<GlobalPos>(iter, length);
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            portal_cooldown = ReadData<VarInt>(iter, length);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
            do_limited_crafting = ReadData<bool>(iter, length);
            common_player_spawn_info = ReadData<CommonPlayerSpawnInfo>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(player_id, container);
#if PROTOCOL_VERSION > 737 /* > 1.16.1 */
            WriteData<bool>(hardcore, container);
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<unsigned char>(game_type, container);
#endif
#if PROTOCOL_VERSION > 718 /* > 1.15.2 */
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<unsigned char>(previous_game_type, container);
#endif
            WriteVector<Identifier>(levels, container);
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<NBT::UnnamedValue>(registry_holder, container);
#endif
#if PROTOCOL_VERSION > 747 /* > 1.16.1 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
            WriteData<NBT::UnnamedValue>(dimension_type, container);
#elif PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<Identifier>(dimension_type, container);
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<Identifier>(dimension, container);
#endif
#else
            WriteData<int>(dimension, container);
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<long long int>(seed, container);
#endif
#if PROTOCOL_VERSION < 477 /* < 1.14 */
            WriteData<unsigned char>(difficulty, container);
#endif
#if PROTOCOL_VERSION < 749 /* < 1.16.2 */
            WriteData<unsigned char>(max_players, container);
#else
            WriteData<VarInt>(max_players, container);
#endif
#if PROTOCOL_VERSION < 719 /* < 1.16 */
            WriteData<std::string>(level_type, container);
#endif
#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
            WriteData<VarInt>(chunk_radius, container);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
            WriteData<VarInt>(simulation_distance, container);
#endif
            WriteData<bool>(reduced_debug_info, container);
#if PROTOCOL_VERSION > 565 /* > 1.14.4 */
            WriteData<bool>(show_death_screen, container);
#endif
#if PROTOCOL_VERSION > 718 /* > 1.15.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<bool>(is_debug, container);
            WriteData<bool>(is_flat, container);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteOptional<GlobalPos>(last_death_location, container);
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<VarInt>(portal_cooldown, container);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
            WriteData<bool>(do_limited_crafting, container);
            WriteData<CommonPlayerSpawnInfo>(common_player_spawn_info, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["player_id"] = player_id;
#if PROTOCOL_VERSION > 737 /* > 1.16.1 */
            output["hardcore"] = hardcore;
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            output["game_type"] = game_type;
#endif
#if PROTOCOL_VERSION > 718 /* > 1.15.2 */
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            output["previous_game_type"] = previous_game_type;
#endif
            output["levels"] = levels;
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            output["registry_holder"] = registry_holder;
#endif

#if PROTOCOL_VERSION > 747 /* > 1.16.1 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            output["dimension_type"] = dimension_type;
#endif
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            output["dimension"] = dimension;
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            output["seed"] = seed;
#endif
            output["difficulty"] = difficulty;
            output["max_players"] = max_players;
#if PROTOCOL_VERSION < 719 /* < 1.16 */
            output["level_type"] = level_type;
#endif
#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
            output["chunk_radius"] = chunk_radius;
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
            output["simulation_distance"] = simulation_distance;
#endif
            output["reduced_debug_info"] = reduced_debug_info;
#if PROTOCOL_VERSION > 565 /* > 1.14.4 */
            output["show_death_screen"] = show_death_screen;
#endif
#if PROTOCOL_VERSION > 718 /* > 1.15.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            output["is_debug"] = is_debug;
            output["is_flat"] = is_flat;
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            if (last_death_location.has_value())
            {
                output["last_death_location"] = last_death_location.value();
            }
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
            output["portal_cooldown"] = portal_cooldown;
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
            output["do_limited_crafting"] = do_limited_crafting;
            output["common_player_spawn_info"] = common_player_spawn_info;
#endif

            return output;
        }

    private:
        int player_id = 0;
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        long long int seed = 0;
#endif
#if PROTOCOL_VERSION > 737 /* > 1.16.1 */
        bool hardcore = false;
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        unsigned char game_type = 0;
#endif
#if PROTOCOL_VERSION > 718 /* > 1.15.2 */
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        unsigned char previous_game_type = 0;
#endif
        std::vector<Identifier> levels;
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        NBT::Value registry_holder;
#endif
#if PROTOCOL_VERSION > 747 /* > 1.16.1 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
        NBT::Value dimension_type;
#elif PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        Identifier dimension_type;
#endif
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        Identifier dimension;
#endif
#else
        int dimension = 0;
#endif
        unsigned char difficulty = 0;
#if PROTOCOL_VERSION < 749 /* < 1.16.2 */
        unsigned char max_players = 0;
#else
        int max_players = 0;
#endif
#if PROTOCOL_VERSION < 719 /* < 1.16 */
        std::string level_type;
#endif
#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
        int chunk_radius = 0;
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        int simulation_distance = 0;
#endif
        bool reduced_debug_info = false;
#if PROTOCOL_VERSION > 565 /* > 1.14.4 */
        bool show_death_screen = false;
#endif
#if PROTOCOL_VERSION > 718 /* > 1.15.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        bool is_debug = false;
        bool is_flat = false;
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        std::optional<GlobalPos> last_death_location;
#endif
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        int portal_cooldown = 0;
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        bool do_limited_crafting = false;
        CommonPlayerSpawnInfo common_player_spawn_info;
#endif
    };
} //ProtocolCraft
