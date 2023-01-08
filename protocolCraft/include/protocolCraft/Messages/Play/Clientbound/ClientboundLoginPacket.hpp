#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#if PROTOCOL_VERSION > 758
#include "protocolCraft/Types/GlobalPos.hpp"
#endif
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    class ClientboundLoginPacket : public BaseMessage<ClientboundLoginPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x23;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x25;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x25;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x26;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x25;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x24;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x26;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x26;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x23;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x25;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x24;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Login";
        }

        virtual ~ClientboundLoginPacket() override
        {

        }

        void SetPlayerId(const int player_id_)
        {
            player_id = player_id_;
        }

#if PROTOCOL_VERSION > 551
        void SetSeed(const long long int seed_)
        {
            seed = seed_;
        }
#endif

#if PROTOCOL_VERSION > 737
        void SetHardcore(const bool hardcore_)
        {
            hardcore = hardcore_;
        }
#endif

        void SetGameType(const unsigned char game_type_)
        {
            game_type = game_type_;
        }

#if PROTOCOL_VERSION > 718
        void SetPreviousGameType(const unsigned char previous_game_type_)
        {
            previous_game_type = previous_game_type_;
        }

        void SetLevels(const std::vector<Identifier>& levels_)
        {
            levels = levels_;
        }

        void SetRegistryHolder(const NBT& registry_holder_)
        {
            registry_holder = registry_holder_;
        }

#if PROTOCOL_VERSION > 747 && PROTOCOL_VERSION < 759
        void SetDimensionType(const NBT& dimension_type_)
        {
            dimension_type = dimension_type_;
        }
#elif PROTOCOL_VERSION > 758
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

#if PROTOCOL_VERSION < 477
        void SetDifficulty(const unsigned char difficulty_)
        {
            difficulty = difficulty_;
        }
#endif

#if PROTOCOL_VERSION < 749
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

#if PROTOCOL_VERSION < 719
        void SetLevelType(const std::string& level_type_)
        {
            level_type = level_type_;
        }
#endif

#if PROTOCOL_VERSION >= 477
        void SetChunkRadius(const int chunk_radius_)
        {
            chunk_radius = chunk_radius_;
        }
#endif
#if PROTOCOL_VERSION > 756
        void SetSimulationDistance(const int simulation_distance_)
        {
            simulation_distance = simulation_distance_;
        }
#endif

        void SetReducedDebugInfo(const bool reduced_debug_info_)
        {
            reduced_debug_info = reduced_debug_info_;
        }

#if PROTOCOL_VERSION > 565
        void SetShowDeathScreen(const bool show_death_screen_)
        {
            show_death_screen = show_death_screen_;
        }
#endif

#if PROTOCOL_VERSION > 718
        void SetIsDebug(const bool is_debug_)
        {
            is_debug = is_debug_;
        }

        void SetIsFlat(const bool is_flat_)
        {
            is_flat = is_flat_;
        }
#endif

#if PROTOCOL_VERSION > 758
        void SetLastDeathLocation(const std::optional<GlobalPos>& last_death_location_)
        {
            last_death_location = last_death_location_;
        }
#endif


        const int GetPlayerId() const
        {
            return player_id;
        }

#if PROTOCOL_VERSION > 551
        const long long int GetSeed() const
        {
            return seed;
        }
#endif

#if PROTOCOL_VERSION > 737
        const bool GetHardcore() const
        {
            return hardcore;
        }
#endif

        const unsigned char GetGameType() const
        {
            return game_type;
        }

#if PROTOCOL_VERSION > 718
        const unsigned char GetPreviousGameType() const
        {
            return previous_game_type;
        }

        const std::vector<Identifier>& GetLevels() const
        {
            return levels;
        }

        const NBT& GetRegistryHolder() const
        {
            return registry_holder;
        }

#if PROTOCOL_VERSION > 747 && PROTOCOL_VERSION < 759
        const NBT& GetDimensionType() const
        {
            return dimension_type;
        }
#elif PROTOCOL_VERSION > 758
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
        const int GetDimension() const
        {
            return dimension;
        }
#endif

#if PROTOCOL_VERSION < 477
        const unsigned char GetDifficulty() const
        {
            return difficulty;
        }
#endif

#if PROTOCOL_VERSION < 749
        const unsigned char GetMaxPlayers() const
        {
            return max_players;
        }
#else
        const int GetMaxPlayers() const
        {
            return max_players;
        }
#endif

#if PROTOCOL_VERSION < 719
        const std::string& GetLevelType() const
        {
            return level_type;
        }
#endif

#if PROTOCOL_VERSION >= 477
        const int GetChunkRadius() const
        {
            return chunk_radius;
        }
#endif
#if PROTOCOL_VERSION > 756
        const int GetSimulationDistance() const
        {
            return simulation_distance;
        }
#endif

        const bool GetReducedDebugInfo() const
        {
            return reduced_debug_info;
        }

#if PROTOCOL_VERSION > 565
        const bool GetShowDeathScreen() const
        {
            return show_death_screen;
        }
#endif
#if PROTOCOL_VERSION > 718
        const bool GetIsDebug() const
        {
            return is_debug;
        }

        const bool GetIsFlat() const
        {
            return is_flat;
        }
#endif

#if PROTOCOL_VERSION > 758
        const std::optional<GlobalPos>& GetLastDeathLocation() const
        {
            return last_death_location;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            player_id = ReadData<int>(iter, length);
#if PROTOCOL_VERSION > 737
            hardcore = ReadData<bool>(iter, length);
#endif
            game_type = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION > 718
            previous_game_type = ReadData<unsigned char>(iter, length);
            levels = ReadVector<Identifier>(iter, length);
            registry_holder = ReadData<NBT>(iter, length);
#if PROTOCOL_VERSION > 747
#if PROTOCOL_VERSION < 759
            dimension_type = ReadData<NBT>(iter, length);
#else
            dimension_type = ReadData<Identifier>(iter, length);
#endif
#endif
            dimension = ReadData<Identifier>(iter, length);
#else
            dimension = ReadData<int>(iter, length);
#endif
#if PROTOCOL_VERSION > 551
            seed = ReadData<long long int>(iter, length);
#endif
#if PROTOCOL_VERSION < 477
            difficulty = ReadData<unsigned char>(iter, length);
#endif
#if PROTOCOL_VERSION < 749
            max_players = ReadData<unsigned char>(iter, length);
#else
            max_players = ReadData<VarInt>(iter, length);
#endif
#if PROTOCOL_VERSION < 719
            level_type = ReadData<std::string>(iter, length);
#endif
#if PROTOCOL_VERSION >= 477
            chunk_radius = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION > 756
            simulation_distance = ReadData<VarInt>(iter, length);
#endif
#endif
            reduced_debug_info = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 565
            show_death_screen = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 718
            is_debug = ReadData<bool>(iter, length);
            is_flat = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 758
            last_death_location = ReadOptional<GlobalPos>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(player_id, container);
#if PROTOCOL_VERSION > 737
            WriteData<bool>(hardcore, container);
#endif
            WriteData<unsigned char>(game_type, container);
#if PROTOCOL_VERSION > 718
            WriteData<unsigned char>(previous_game_type, container);
            WriteVector<Identifier>(levels, container);
            WriteData<NBT>(registry_holder, container);
#if PROTOCOL_VERSION > 747
#if PROTOCOL_VERSION < 759
            WriteData<NBT>(dimension_type, container);
#else
            WriteData<Identifier>(dimension_type, container);
#endif
#endif
            WriteData<Identifier>(dimension, container);
#else
            WriteData<int>(dimension, container);
#endif
#if PROTOCOL_VERSION > 551
            WriteData<long long int>(seed, container);
#endif
#if PROTOCOL_VERSION < 477
            WriteData<unsigned char>(difficulty, container);
#endif
#if PROTOCOL_VERSION < 749
            WriteData<unsigned char>(max_players, container);
#else
            WriteData<VarInt>(max_players, container);
#endif
#if PROTOCOL_VERSION < 719
            WriteData<std::string>(level_type, container);
#endif
#if PROTOCOL_VERSION >= 477
            WriteData<VarInt>(chunk_radius, container);
#endif
#if PROTOCOL_VERSION > 756
            WriteData<VarInt>(simulation_distance, container);
#endif
            WriteData<bool>(reduced_debug_info, container);
#if PROTOCOL_VERSION > 565
            WriteData<bool>(show_death_screen, container);
#endif
#if PROTOCOL_VERSION > 718
            WriteData<bool>(is_debug, container);
            WriteData<bool>(is_flat, container);
#endif
#if PROTOCOL_VERSION > 758
            WriteOptional<GlobalPos>(last_death_location, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["player_id"] = player_id;
#if PROTOCOL_VERSION > 737
            output["hardcore"] = hardcore;
#endif
            output["game_type"] = game_type;
#if PROTOCOL_VERSION > 718
            output["previous_game_type"] = previous_game_type;
            output["levels"] = nlohmann::json::array();
            for (const auto& l : levels)
            {
                output["levels"].push_back(l.Serialize());
            }
            output["registry_holder"] = registry_holder.Serialize();

#if PROTOCOL_VERSION > 747
            output["dimension_type"] = dimension_type.Serialize();
#endif
            output["dimension"] = dimension.Serialize();
#else
            output["dimension"] = dimension;
#endif
#if PROTOCOL_VERSION > 551
            output["seed"] = seed;
#endif
            output["difficulty"] = difficulty;
            output["max_players"] = max_players;
#if PROTOCOL_VERSION < 719
            output["level_type"] = level_type;
#endif
#if PROTOCOL_VERSION >= 477
            output["chunk_radius"] = chunk_radius;
#endif
#if PROTOCOL_VERSION > 756
            output["simulation_distance"] = simulation_distance;
#endif
            output["reduced_debug_info"] = reduced_debug_info;
#if PROTOCOL_VERSION > 565
            output["show_death_screen"] = show_death_screen;
#endif
#if PROTOCOL_VERSION > 718
            output["is_debug"] = is_debug;
            output["is_flat"] = is_flat;
#endif
#if PROTOCOL_VERSION > 758
            if (last_death_location.has_value())
            {
                output["last_death_location"] = last_death_location.value().Serialize();
            }
#endif

            return output;
        }

    private:
        int player_id;
#if PROTOCOL_VERSION > 551
        long long int seed;
#endif
#if PROTOCOL_VERSION > 737
        bool hardcore;
#endif
        unsigned char game_type;
#if PROTOCOL_VERSION > 718
        unsigned char previous_game_type;
        std::vector<Identifier> levels;
        NBT registry_holder;
#if PROTOCOL_VERSION > 747 && PROTOCOL_VERSION < 759
        NBT dimension_type;
#elif PROTOCOL_VERSION > 758
        Identifier dimension_type;
#endif
        Identifier dimension;
#else
        int dimension;
#endif
        unsigned char difficulty;
#if PROTOCOL_VERSION < 749
        unsigned char max_players;
#else
        int max_players;
#endif
#if PROTOCOL_VERSION < 719
        std::string level_type;
#endif
#if PROTOCOL_VERSION >= 477
        int chunk_radius;
#endif
#if PROTOCOL_VERSION > 756
        int simulation_distance;
#endif
        bool reduced_debug_info;
#if PROTOCOL_VERSION > 565
        bool show_death_screen;
#endif
#if PROTOCOL_VERSION > 718
        bool is_debug;
        bool is_flat;
#endif
#if PROTOCOL_VERSION > 758
        std::optional<GlobalPos> last_death_location;
#endif
    };
} //ProtocolCraft
