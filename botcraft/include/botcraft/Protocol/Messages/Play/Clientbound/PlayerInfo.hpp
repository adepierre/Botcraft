#pragma once

#include <iostream>
#include <string>
#include <map>

#include "botcraft/Protocol/BaseMessage.hpp"
#include "botcraft/Protocol/Types/Chat.hpp"
#include "botcraft/Game/Enums.hpp"
#include "botcraft/Game/OtherPlayer.hpp"

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
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575
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

        const std::map<std::string, OtherPlayer>& GetPlayers() const
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
                switch (action)
                {
                case 0:
                {
                    players[uuid].SetName(ReadString(iter, length));
                    const int number_of_properties = ReadVarInt(iter, length);
                    players[uuid].SetProperties(std::vector<PlayerProperty>(number_of_properties));
                    for (int j = 0; j < number_of_properties; ++j)
                    {
                        players[uuid].GetProperties()[j].Read(iter, length);
                    }

                    players[uuid].SetGamemode((GameMode)ReadVarInt(iter, length));
                    players[uuid].SetPing(ReadVarInt(iter, length));
                    players[uuid].SetHasDisplayName(ReadData<bool>(iter, length));
                    if (players[uuid].GetHasDisplayName())
                    {
                        Chat c;
                        c.Read(iter, length);
                        players[uuid].SetDisplayName(c);
                    }
                }
                    break;
                case 1:
                    gamemode[uuid] = (GameMode)ReadVarInt(iter, length);
                    break;
                case 2:
                    ping[uuid] = ReadVarInt(iter, length);
                    break;
                case 3:
                    has_display_name[uuid] = ReadData<bool>(iter, length);
                    if (has_display_name[uuid])
                    {
                        display_name[uuid].Read(iter, length);
                    }
                    break;
                case 4:
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

    private:
        int action;
        std::map<std::string, OtherPlayer> players;
        std::map<std::string, GameMode> gamemode;
        std::map<std::string, int> ping;
        std::map<std::string, bool> has_display_name;
        std::map<std::string, Chat> display_name;
        std::vector<std::string> removed;
    };
} //Botcraft