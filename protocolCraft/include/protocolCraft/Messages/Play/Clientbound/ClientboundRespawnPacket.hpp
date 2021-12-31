#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/enums.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundRespawnPacket : public BaseMessage<ClientboundRespawnPacket>
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x3A;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x39;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x3D;
#elif PROTOCOL_VERSION == 757 // 1.18
            return 0x3D;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Respawn";
        }

        virtual ~ClientboundRespawnPacket() override
        {

        }

#if PROTOCOL_VERSION > 729
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

#if PROTOCOL_VERSION > 551
        void SetSeed(const long long int seed_)
        {
            seed = seed_;
        }
#endif

#if PROTOCOL_VERSION < 477
        void SetDifficulty(const int difficulty_)
        {
            difficulty = difficulty_;
        }
#endif

        void SetPlayerGameType(const int player_game_type_)
        {
            player_game_type = player_game_type_;
        }

#if PROTOCOL_VERSION < 730
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

        void SetKeepAllPlayerData(const bool keep_all_player_data_)
        {
            keep_all_player_data = keep_all_player_data_;
        }
#endif

#if PROTOCOL_VERSION > 729
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

#if PROTOCOL_VERSION > 551
        const long long int GetSeed() const
        {
            return seed;
        }
#endif

#if PROTOCOL_VERSION < 477
        const int GetDifficulty() const
        {
            return difficulty;
        }
#endif

        const int GetPlayerGameType() const
        {
            return player_game_type;
        }

#if PROTOCOL_VERSION < 730
        const std::string& GetLevelType() const
        {
            return level_type;
        }
#else
        const int GetPreviousPlayerGameType() const
        {
            return previous_player_game_type;
        }

        const bool GetIsDebug() const
        {
            return is_debug;
        }

        const bool GetIsFlat() const
        {
            return is_flat;
        }

        const bool GetKeepAllPlayerData() const
        {
            return keep_all_player_data;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION > 729
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
            player_game_type = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION < 730
            level_type = ReadData<std::string>(iter, length);
#else
            previous_player_game_type = ReadData<unsigned char>(iter, length);
            is_debug = ReadData<bool>(iter, length);
            is_flat = ReadData<bool>(iter, length);
            keep_all_player_data = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION > 729
#if PROTOCOL_VERSION > 747
            dimension_type.Write(container);
#endif
            dimension.Write(container);
#else
            WriteData<int>((int)dimension, container);
#endif
#if PROTOCOL_VERSION > 551
            WriteData<long long int>(seed, container);
#endif
#if PROTOCOL_VERSION < 477
            WriteData<unsigned char>((unsigned char)difficulty, container);
#endif
            WriteData<unsigned char>((unsigned char)player_game_type, container);
#if PROTOCOL_VERSION < 730
            WriteData<std::string>(level_type, container);
#else
            WriteData<unsigned char>((unsigned char)previous_player_game_type, container);
            WriteData<bool>(is_debug, container);
            WriteData<bool>(is_flat, container);
            WriteData<bool>(keep_all_player_data, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION > 729
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
#if PROTOCOL_VERSION < 477
            output["difficulty"] = difficulty;
#endif
            output["player_game_type"] = player_game_type;
#if PROTOCOL_VERSION < 730
            output["level_type"] = level_type;
#else
            output["previous_player_game_type"] = previous_player_game_type;
            output["is_debug"] = is_debug;
            output["is_flat"] = is_flat;
            output["keep_all_player_data"] = keep_all_player_data;
#endif

            return output;
    }

    private:
#if PROTOCOL_VERSION > 729
#if PROTOCOL_VERSION > 747
        NBT dimension_type;
#endif
        Identifier dimension;
#else
        int dimension;
#endif
#if PROTOCOL_VERSION > 551
        long long int seed;
#endif
#if PROTOCOL_VERSION < 477
        int difficulty;
#endif
        int player_game_type;
#if PROTOCOL_VERSION < 730
        std::string level_type;
#else
        int previous_player_game_type;
        bool is_debug;
        bool is_flat;
        bool keep_all_player_data;
#endif
    };
} //ProtocolCraft