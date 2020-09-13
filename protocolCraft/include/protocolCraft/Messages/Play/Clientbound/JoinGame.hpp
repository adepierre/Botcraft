#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class JoinGame : public BaseMessage<JoinGame>
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
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x24;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Join Game";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

#if PROTOCOL_VERSION > 737
        void SetIsHardcore(const bool is_hardcore_)
        {
            is_hardcore = is_hardcore_;
        }
#endif

        void SetGamemode(const unsigned char gamemode_)
        {
            gamemode = gamemode_;
        }

#if PROTOCOL_VERSION > 718
        void SetPreviousGamemode(const unsigned char previous_gamemode_)
        {
            previous_gamemode = previous_gamemode_;
        }

        void SetWorldCount(const int world_count_)
        {
            world_count = world_count_;
        }

        void SetWorldNames(const std::vector<Identifier>& world_names_)
        {
            world_names = world_names_;
        }

        void SetDimensionCodec(const NBT& dimension_codec_)
        {
            dimension_codec = dimension_codec_;
        }

#if PROTOCOL_VERSION > 747
        void SetDimension(const NBT& dimension_)
#else
        void SetDimension(const Identifier& dimension_)
#endif
        {
            dimension = dimension_;
        }

        void SetWorldName(const Identifier& world_name_)
        {
            world_name = world_name_;
        }
#else
        void SetDimension(const int dimension_)
        {
            dimension = dimension_;
        }
#endif

#if PROTOCOL_VERSION > 551
        void SetHashedSeed(const long long int hashed_seed_)
        {
            hashed_seed = hashed_seed_;
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
        void SetViewDistance(const int view_distance_)
        {
            view_distance = view_distance_;
        }
#endif

        void SetReducedDebugInfo(const bool reduced_debug_info_)
        {
            reduced_debug_info = reduced_debug_info_;
        }

#if PROTOCOL_VERSION > 565
        void SetEnableRespawnScreen(const bool enable_respawn_screen_)
        {
            enable_respawn_screen = enable_respawn_screen_;
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

        const int GetEntityId() const
        {
            return entity_id;
        }

#if PROTOCOL_VERSION > 737
        const bool GetIsHardcore() const
        {
            return is_hardcore;
        }
#endif

        const unsigned char GetGamemode() const
        {
            return gamemode;
        }

#if PROTOCOL_VERSION > 718
        const unsigned char GetPreviousGamemode() const
        {
            return previous_gamemode;
        }

        const int GetWorldCount() const
        {
            return world_count;
        }

        const std::vector<Identifier>& GetWorldNames() const
        {
            return world_names;
        }

        const NBT& GetDimensionCodec() const
        {
            return dimension_codec;
        }

#if PROTOCOL_VERSION > 747
        const NBT& GetDimension() const
#else
        const Identifier& GetDimension() const
#endif
        {
            return dimension;
        }

        const Identifier& GetWorldName() const
        {
            return world_name;
        }
#else
        const int GetDimension() const
        {
            return dimension;
        }
#endif

#if PROTOCOL_VERSION > 551
		const long long int GetHashedSeed() const
		{
			return hashed_seed;
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
        const int GetViewDistance() const
        {
            return view_distance;
        }
#endif

        const bool GetReducedDebugInfo() const
        {
            return reduced_debug_info;
        }

#if PROTOCOL_VERSION > 565
		const bool GetEnableRespawnScreen() const
		{
			return enable_respawn_screen;
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
            entity_id = ReadData<int>(iter, length);
#if PROTOCOL_VERSION > 737
            is_hardcore = ReadData<bool>(iter, length);
#endif
            gamemode = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION > 718
            previous_gamemode = ReadData<unsigned char>(iter, length);
            world_count = ReadVarInt(iter, length);
            world_names = std::vector<Identifier>(world_count);
            for (int i = 0; i < world_count; ++i)
            {
                world_names[i] = ReadString(iter, length);
            }
            dimension_codec.Read(iter, length);
#if PROTOCOL_VERSION > 747
            dimension.Read(iter, length);
#else
            dimension = ReadString(iter, length);
#endif
            world_name = ReadString(iter, length);
#else
            dimension = ReadData<int>(iter, length);
#endif
#if PROTOCOL_VERSION > 551
			hashed_seed = ReadData<long long int>(iter, length);
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
            view_distance = ReadVarInt(iter, length);
#endif
            reduced_debug_info = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 565
			enable_respawn_screen = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 718
            is_debug = ReadData<bool>(iter, length);
            is_flat = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(entity_id, container);
#if PROTOCOL_VERSION > 737
            WriteData<bool>(is_hardcore, container);
#endif
            WriteData<unsigned char>(gamemode, container);
#if PROTOCOL_VERSION > 718
            WriteData<unsigned char>(previous_gamemode, container);
            WriteVarInt(world_count, container);
            for (int i = 0; i < world_count; ++i)
            {
                WriteString(world_names[i], container);
            }
            dimension_codec.Write(container);
#if PROTOCOL_VERSION > 747
            dimension.Write(container);
#else
            WriteString(dimension, container);
#endif
            WriteString(world_name, container);
#else
            WriteData<int>(dimension, container);
#endif
#if PROTOCOL_VERSION > 551
            WriteData<long long int>(hashed_seed, container);
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
            WriteVarInt(view_distance, container);
#endif
            WriteData<bool>(reduced_debug_info, container);
#if PROTOCOL_VERSION > 565
            WriteData<bool>(enable_respawn_screen, container);
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

            object["entity_id"] = picojson::value((double)entity_id);
#if PROTOCOL_VERSION > 737
            object["is_hardcore"] = picojson::value(is_hardcore);
#endif
            object["gamemode"] = picojson::value((double)gamemode);
#if PROTOCOL_VERSION > 718
            object["previous_gamemode"] = picojson::value((double)previous_gamemode);
            object["world_count"] = picojson::value((double)world_count);
            object["world_names"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["world_names"].get<picojson::array>();
            for (int i = 0; i < world_count; ++i)
            {
                array.push_back(picojson::value(world_names[i]));
            }
            object["dimension_codec"] = dimension_codec.Serialize();

#if PROTOCOL_VERSION > 747
            object["dimension"] = dimension.Serialize();
#else
            object["dimension"] = picojson::value(dimension);
#endif
            object["world_name"] = picojson::value(world_name);
#else
            object["dimension"] = picojson::value((double)dimension);
#endif
#if PROTOCOL_VERSION > 551
            object["hashed_seed"] = picojson::value((double)hashed_seed);
#endif
            object["difficulty"] = picojson::value((double)difficulty);
            object["max_players"] = picojson::value((double)max_players);
#if PROTOCOL_VERSION < 719
            object["level_type"] = picojson::value(level_type);
#endif
#if PROTOCOL_VERSION >= 477
            object["view_distance"] = picojson::value((double)view_distance);
#endif
            object["reduced_debug_info"] = picojson::value(reduced_debug_info);
#if PROTOCOL_VERSION > 565
            object["enable_respawn_screen"] = picojson::value(enable_respawn_screen);
#endif
#if PROTOCOL_VERSION > 718
            object["is_debug"] = picojson::value(is_debug);
            object["is_flat"] = picojson::value(is_flat);
#endif

            return value;
        }

    private:
        int entity_id;
#if PROTOCOL_VERSION > 737
        bool is_hardcore;
#endif
        unsigned char gamemode;
#if PROTOCOL_VERSION > 718
        unsigned char previous_gamemode;
        int world_count;
        std::vector<Identifier> world_names;
        NBT dimension_codec;
#if PROTOCOL_VERSION > 747
        NBT dimension;
#else
        Identifier dimension;
#endif
        Identifier world_name;
#else
        int dimension;
#endif
#if PROTOCOL_VERSION > 551
		long long int hashed_seed;
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
        int view_distance;
#endif
        bool reduced_debug_info;
#if PROTOCOL_VERSION > 565
		bool enable_respawn_screen;
#endif
#if PROTOCOL_VERSION > 718
        bool is_debug;
        bool is_flat;
#endif
    };
} //ProtocolCraft