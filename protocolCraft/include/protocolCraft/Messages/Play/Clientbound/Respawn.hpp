#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class Respawn : public BaseMessage<Respawn>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x35;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x38;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x3A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x3B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x3A;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Respawn";
        }

#if PROTOCOL_VERSION > 729
        void SetDimension(const Identifier& dimension_)
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

        void SetGamemode(const unsigned char gamemode_)
        {
            gamemode = gamemode_;
        }

#if PROTOCOL_VERSION < 730
        void SetLevelType(const std::string& level_type_)
        {
            level_type = level_type_;
        }
#else
        void SetPreviousGamemode(const unsigned char previous_gamemode_)
        {
            previous_gamemode = previous_gamemode_;
        }

        void SetIsDebug(const bool is_debug_)
        {
            is_debug = is_debug_;
        }

        void SetIsFlat(const bool is_flat_)
        {
            is_flat = is_flat_;
        }

        void SetCopyMetadata(const bool copy_metadata_)
        {
            copy_metadata = copy_metadata_;
        }
#endif

#if PROTOCOL_VERSION > 729
        const Identifier& GetDimension() const
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

        const unsigned char GetGamemode() const
        {
            return gamemode;
        }

#if PROTOCOL_VERSION < 730
        const std::string& GetLevelType() const
        {
            return level_type;
        }
#else
        const unsigned char GetPreviousGamemode() const
        {
            return previous_gamemode;
        }

        const bool GetIsDebug() const
        {
            return is_debug;
        }

        const bool GetIsFlat() const
        {
            return is_flat;
        }

        const bool GetCopyMetadata() const
        {
            return copy_metadata;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION > 729
            dimension = ReadString(iter, length);
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
            gamemode = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION < 730
            level_type = ReadString(iter, length);
#else
            previous_gamemode = ReadData<unsigned char>(iter, length);
            is_debug = ReadData<bool>(iter, length);
            is_flat = ReadData<bool>(iter, length);
            copy_metadata = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION > 729
            WriteString(dimension, container);
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
            WriteData<unsigned char>(gamemode, container);
#if PROTOCOL_VERSION < 730
            WriteString(level_type, container);
#else
            WriteData<unsigned char>(previous_gamemode, container);
            WriteData<bool>(is_debug, container);
            WriteData<bool>(is_flat, container);
            WriteData<bool>(copy_metadata, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

#if PROTOCOL_VERSION > 729
            object["dimension"] = picojson::value(dimension);
            object["world_name"] = picojson::value(world_name);
#else
            object["dimension"] = picojson::value((double)dimension);
#endif
#if PROTOCOL_VERSION > 551
            object["hashed_seed"] = picojson::value((double)hashed_seed);
#endif
#if PROTOCOL_VERSION < 477
            object["difficulty"] = picojson::value((double)difficulty);
#endif
            object["gamemode"] = picojson::value((double)gamemode);
#if PROTOCOL_VERSION < 730
            object["level_type"] = picojson::value(level_type);
#else
            object["previous_gamemode"] = picojson::value((double)previous_gamemode);
            object["is_debug"] = picojson::value(is_debug);
            object["is_flat"] = picojson::value(is_flat);
            object["copy_metadata"] = picojson::value(copy_metadata);
#endif

            return value;
    }

    private:
#if PROTOCOL_VERSION > 729
        Identifier dimension;
        Identifier world_name;
#else
        int dimension;
#endif
#if PROTOCOL_VERSION > 551
		long long int hashed_seed;
#endif
#if PROTOCOL_VERSION < 477
        unsigned char difficulty;
#endif
        unsigned char gamemode;
#if PROTOCOL_VERSION < 730
        std::string level_type;
#else
        unsigned char previous_gamemode;
        bool is_debug;
        bool is_flat;
        bool copy_metadata;
#endif
    };
} //ProtocolCraft