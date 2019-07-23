#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"
#include "botcraft/Game/Enums.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
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
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Join Game";
        }

        const int GetEntityId() const
        {
            return entity_id;
        }

        const unsigned char GetGamemode() const
        {
            return gamemode;
        }

        const Dimension GetDimension() const
        {
            return dimension;
        }

#if PROTOCOL_VERSION < 477
        const Difficulty GetDifficulty() const
        {
            return difficulty;
        }
#endif

        const unsigned char GetMaxPlayers() const
        {
            return max_players;
        }

        const std::string& GetLevelType() const
        {
            return level_type;
        }

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

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            entity_id = ReadData<int>(iter, length);
            gamemode = ReadData<unsigned char>(iter, length);
            dimension = (Dimension)ReadData<int>(iter, length);
#if PROTOCOL_VERSION < 477
            difficulty = (Difficulty)ReadData<unsigned char>(iter, length);
#endif
            max_players = ReadData<unsigned char>(iter, length);
            level_type = ReadString(iter, length);
#if PROTOCOL_VERSION >= 477
            view_distance = ReadVarInt(iter, length);
#endif
            reduced_debug_info = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        int entity_id;
        unsigned char gamemode;
        Dimension dimension;
        Difficulty difficulty;
        unsigned char max_players;
        std::string level_type;
#if PROTOCOL_VERSION >= 477
        int view_distance;
#endif
        bool reduced_debug_info;
    };
} //Botcraft