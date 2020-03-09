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
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Respawn";
        }

        void SetDimension(const int dimension_)
        {
            dimension = dimension_;
        }

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

        void SetLevelType(const std::string& level_type_)
        {
            level_type = level_type_;
        }

        const int GetDimension() const
        {
            return dimension;
        }

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

        const std::string& GetLevelType() const
        {
            return level_type;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            dimension = ReadData<int>(iter, length);
#if PROTOCOL_VERSION > 551
			hashed_seed = ReadData<long long int>(iter, length);
#endif
#if PROTOCOL_VERSION < 477
            difficulty = ReadData<unsigned char>(iter, length);
#endif
            gamemode = ReadData<unsigned char>(iter, length);
            level_type = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(dimension, container);
#if PROTOCOL_VERSION > 551
            WriteData<long long int>(hashed_seed, container);
#endif
#if PROTOCOL_VERSION < 477
            WriteData<unsigned char>(difficulty, container);
#endif
            WriteData<unsigned char>(gamemode, container);
            WriteString(level_type, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["dimension"] = picojson::value((double)dimension);
#if PROTOCOL_VERSION > 551
            object["hashed_seed"] = picojson::value((double)hashed_seed);
#endif
#if PROTOCOL_VERSION < 477
            object["difficulty"] = picojson::value((double)difficulty);
#endif
            object["gamemode"] = picojson::value((double)gamemode);
            object["level_type"] = picojson::value(level_type);

            return value;
    }

    private:
        int dimension;
#if PROTOCOL_VERSION > 551
		long long int hashed_seed;
#endif
#if PROTOCOL_VERSION < 477
        unsigned char difficulty;
#endif
        unsigned char gamemode;
        std::string level_type;
    };
} //ProtocolCraft