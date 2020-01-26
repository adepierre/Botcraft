#pragma once

#include <iostream>
#include <string>
#include <map>

#include "botcraft/Protocol/BaseMessage.hpp"
#include "botcraft/Protocol/Types/Chat.hpp"
#include "botcraft/Game/Enums.hpp"
#include "botcraft/Game/PlayerInformation.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    // Was Player List Item in 1.12.2
    class PlayerInfo : public BaseMessage<PlayerInfo>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x2E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x30;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x33;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x34;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player List Item";
        }

        const int GetAction() const
        {
            return action;
        }

        const std::map<std::string, PlayerInformation>& GetPlayers() const
        {
            return players;
        }

        const std::map<std::string, GameMode>& GetGamemode() const
        {
            return gamemode;
        }

        const std::map<std::string, int>& GetPing() const
        {
            return ping;
        }

        const std::map<std::string, bool>& GetHasDisplayName() const
        {
            return has_display_name;
        }

        const std::map<std::string, Chat>& GetDisplayName() const
        {
            return display_name;
        }

        const std::vector<std::string>& GetRemoved() const
        {
            return removed;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            action = ReadVarInt(iter, length);
            const int number_of_players = ReadVarInt(iter, length);
            for (int i = 0; i < number_of_players; ++i)
            {
                std::string uuid = ReadRawString(iter, length, 16);
                switch ((PlayerInfoAction)action)
                {
                case PlayerInfoAction::AddPlayer:
                {
                    players[uuid].Read(iter, length);
                }
                    break;
                case PlayerInfoAction::UpdateGamemode:
                    gamemode[uuid] = (GameMode)ReadVarInt(iter, length);
                    break;
                case PlayerInfoAction::UpdateLatency:
                    ping[uuid] = ReadVarInt(iter, length);
                    break;
                case PlayerInfoAction::UpdateDisplayName:
                    has_display_name[uuid] = ReadData<bool>(iter, length);
                    if (has_display_name[uuid])
                    {
                        display_name[uuid].Read(iter, length);
                    }
                    break;
                case PlayerInfoAction::RemovePlayer:
                    removed.push_back(uuid);
                    break;
                default:
                    break;
                }
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["action"] = picojson::value((double)action);
            object["players"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["players"].get<picojson::array>();

            switch ((PlayerInfoAction)action)
            {
            case PlayerInfoAction::AddPlayer:
                array.reserve(players.size());
                for (auto it = players.begin(); it != players.end(); ++it)
                {
                    array.push_back(it->second.Serialize());
                }
                break;
            case PlayerInfoAction::UpdateGamemode:
                array.reserve(gamemode.size());
                for (auto it = gamemode.begin(); it != gamemode.end(); ++it)
                {
                    array.push_back(picojson::value((double)it->second));
                }
                break;
            case PlayerInfoAction::UpdateLatency:
                array.reserve(ping.size());
                for (auto it = ping.begin(); it != ping.end(); ++it)
                {
                    array.push_back(picojson::value((double)it->second));
                }
                break;
            case PlayerInfoAction::UpdateDisplayName:
                array.reserve(display_name.size());
                for (auto it = display_name.begin(); it != display_name.end(); ++it)
                {
                    array.push_back(it->second.Serialize());
                }
                break;
            case PlayerInfoAction::RemovePlayer:
                array.reserve(display_name.size());
                for (auto it = removed.begin(); it != removed.end(); ++it)
                {
                    array.push_back(picojson::value(*it));
                }
                break;
            default:
                break;
            }

            return value;
        }

    private:
        int action;
        std::map<std::string, PlayerInformation> players;
        std::map<std::string, GameMode> gamemode;
        std::map<std::string, int> ping;
        std::map<std::string, bool> has_display_name;
        std::map<std::string, Chat> display_name;
        std::vector<std::string> removed;
    };
} //Botcraft