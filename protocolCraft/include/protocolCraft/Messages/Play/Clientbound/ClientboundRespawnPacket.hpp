#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/enums.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#if PROTOCOL_VERSION > 747 && PROTOCOL_VERSION < 759
#include "protocolCraft/Types/NBT/NBT.hpp"
#endif
#if PROTOCOL_VERSION > 758
#include "protocolCraft/Types/GlobalPos.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundRespawnPacket : public BaseMessage<ClientboundRespawnPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x3E;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x41;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Respawn";

        virtual ~ClientboundRespawnPacket() override
        {

        }

#if PROTOCOL_VERSION > 729
#if PROTOCOL_VERSION > 747 && PROTOCOL_VERSION < 759
        void SetDimensionType(const NBT::Value& dimension_type_)
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

#if PROTOCOL_VERSION < 761
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
#if PROTOCOL_VERSION > 758
        void SetLastDeathLocation(const std::optional<GlobalPos>& last_death_location_)
        {
            last_death_location = last_death_location_;
        }
#endif

#if PROTOCOL_VERSION > 729
#if PROTOCOL_VERSION > 747 && PROTOCOL_VERSION < 759
        const NBT::Value& GetDimensionType() const
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
        int GetDimension() const
        {
            return dimension;
        }
#endif

#if PROTOCOL_VERSION > 551
        long long int GetSeed() const
        {
            return seed;
        }
#endif

#if PROTOCOL_VERSION < 477
        int GetDifficulty() const
        {
            return difficulty;
        }
#endif

        int GetPlayerGameType() const
        {
            return player_game_type;
        }

#if PROTOCOL_VERSION < 730
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

#if PROTOCOL_VERSION < 761
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

#if PROTOCOL_VERSION > 758
        const std::optional<GlobalPos>& GetLastDeathLocation() const
        {
            return last_death_location;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION > 729
#if PROTOCOL_VERSION > 747
#if PROTOCOL_VERSION < 759
            dimension_type = ReadData<NBT::Value>(iter, length);
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
            player_game_type = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION < 730
            level_type = ReadData<std::string>(iter, length);
#else
            previous_player_game_type = ReadData<unsigned char>(iter, length);
            is_debug = ReadData<bool>(iter, length);
            is_flat = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION < 761
            keep_all_player_data = ReadData<bool>(iter, length);
#else
            data_to_keep = ReadData<unsigned char>(iter, length);
#endif
#endif
#if PROTOCOL_VERSION > 758
            last_death_location = ReadOptional<GlobalPos>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION > 729
#if PROTOCOL_VERSION > 747
#if PROTOCOL_VERSION < 759
            WriteData<NBT::Value>(dimension_type, container);
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
            WriteData<unsigned char>((unsigned char)difficulty, container);
#endif
            WriteData<unsigned char>((unsigned char)player_game_type, container);
#if PROTOCOL_VERSION < 730
            WriteData<std::string>(level_type, container);
#else
            WriteData<unsigned char>((unsigned char)previous_player_game_type, container);
            WriteData<bool>(is_debug, container);
            WriteData<bool>(is_flat, container);
#if PROTOCOL_VERSION < 761
            WriteData<bool>(keep_all_player_data, container);
#else
            WriteData<unsigned char>(data_to_keep, container);
#endif
#endif
#if PROTOCOL_VERSION > 758
            WriteOptional<GlobalPos>(last_death_location, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION > 729
#if PROTOCOL_VERSION > 747
            output["dimension_type"] = dimension_type;
#endif
            output["dimension"] = dimension;
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
#if PROTOCOL_VERSION < 761
            output["keep_all_player_data"] = keep_all_player_data;
#else
            output["data_to_keep"] = data_to_keep;
#endif
#endif
#if PROTOCOL_VERSION > 758
            if (last_death_location.has_value())
            {
                output["last_death_location"] = last_death_location.value();
            }
#endif

            return output;
    }

    private:
#if PROTOCOL_VERSION > 729
#if PROTOCOL_VERSION > 747 && PROTOCOL_VERSION < 759
        NBT::Value dimension_type;
#elif PROTOCOL_VERSION > 758
        Identifier dimension_type;
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
#if PROTOCOL_VERSION < 761
        bool keep_all_player_data;
#else
        unsigned char data_to_keep;
#endif
#endif
#if PROTOCOL_VERSION > 758
        std::optional<GlobalPos> last_death_location;
#endif
    };
} //ProtocolCraft
