#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x25;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x24;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x26;
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

#if PROTOCOL_VERSION > 747
        void SetDimensionType(const NBT& dimension_type_)
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

#if PROTOCOL_VERSION > 747
        const NBT& GetDimensionType() const
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
            int levels_size = ReadVarInt(iter, length);
            levels = std::vector<Identifier>(levels_size);
            for (int i = 0; i < levels_size; ++i)
            {
                levels[i].Read(iter, length);
            }
            registry_holder.Read(iter, length);
#if PROTOCOL_VERSION > 747
            dimension_type.Read(iter, length);
#endif
            dimension.Read(iter, length);
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
            max_players = ReadVarInt(iter, length);
#endif
#if PROTOCOL_VERSION < 719
            level_type = ReadString(iter, length);
#endif
#if PROTOCOL_VERSION >= 477
            chunk_radius = ReadVarInt(iter, length);
#endif
            reduced_debug_info = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 565
			show_death_screen = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 718
            is_debug = ReadData<bool>(iter, length);
            is_flat = ReadData<bool>(iter, length);
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
            WriteVarInt(levels.size(), container);
            for (int i = 0; i < levels.size(); ++i)
            {
                levels[i].Write(container);
            }
            registry_holder.Write(container);
#if PROTOCOL_VERSION > 747
            dimension_type.Write(container);
#endif
            dimension.Write(container);
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
            WriteVarInt(max_players, container);
#endif
#if PROTOCOL_VERSION < 719
            WriteString(level_type, container);
#endif
#if PROTOCOL_VERSION >= 477
            WriteVarInt(chunk_radius, container);
#endif
            WriteData<bool>(reduced_debug_info, container);
#if PROTOCOL_VERSION > 565
            WriteData<bool>(show_death_screen, container);
#endif
#if PROTOCOL_VERSION > 718
            WriteData<bool>(is_debug, container);
            WriteData<bool>(is_flat, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["player_id"] = picojson::value((double)player_id);
#if PROTOCOL_VERSION > 737
            object["hardcore"] = picojson::value(hardcore);
#endif
            object["game_type"] = picojson::value((double)game_type);
#if PROTOCOL_VERSION > 718
            object["previous_game_type"] = picojson::value((double)previous_game_type);
            object["levels"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["levels"].get<picojson::array>();
            for (int i = 0; i < levels.size(); ++i)
            {
                array.push_back(levels[i].Serialize());
            }
            object["registry_holder"] = registry_holder.Serialize();

#if PROTOCOL_VERSION > 747
            object["dimension_type"] = dimension_type.Serialize();
#endif
            object["dimension"] = dimension.Serialize();
#else
            object["dimension"] = picojson::value((double)dimension);
#endif
#if PROTOCOL_VERSION > 551
            object["seed"] = picojson::value((double)seed);
#endif
            object["difficulty"] = picojson::value((double)difficulty);
            object["max_players"] = picojson::value((double)max_players);
#if PROTOCOL_VERSION < 719
            object["level_type"] = picojson::value(level_type);
#endif
#if PROTOCOL_VERSION >= 477
            object["chunk_radius"] = picojson::value((double)chunk_radius);
#endif
            object["reduced_debug_info"] = picojson::value(reduced_debug_info);
#if PROTOCOL_VERSION > 565
            object["show_death_screen"] = picojson::value(show_death_screen);
#endif
#if PROTOCOL_VERSION > 718
            object["is_debug"] = picojson::value(is_debug);
            object["is_flat"] = picojson::value(is_flat);
#endif

            return value;
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
#if PROTOCOL_VERSION > 747
        NBT dimension_type;
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
        bool reduced_debug_info;
#if PROTOCOL_VERSION > 565
		bool show_death_screen;
#endif
#if PROTOCOL_VERSION > 718
        bool is_debug;
        bool is_flat;
#endif
    };
} //ProtocolCraft