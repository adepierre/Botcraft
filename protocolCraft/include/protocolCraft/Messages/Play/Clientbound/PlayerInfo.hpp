#pragma once

#include <string>
#include <map>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"
#include "protocolCraft/Types/PlayerInformation.hpp"

namespace ProtocolCraft
{
    enum class PlayerInfoAction
    {
        AddPlayer = 0,
        UpdateGamemode = 1,
        UpdateLatency = 2,
        UpdateDisplayName = 3,
        RemovePlayer = 4
    };

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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x33;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x32;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
#if PROTOCOL_VERSION == 340
            return "Player List Item";
#else
            return "Player Info";
#endif
        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetPlayers(const std::map<UUID, PlayerInformation>& players_)
        {
            players = players_;
        }

        void SetGamemode(const std::map<UUID, int>& gamemode_)
        {
            gamemode = gamemode_;
        }

        void SetPing(const std::map<UUID, int>& ping_)
        {
            ping = ping_;
        }

        void SetHasDisplayName(const std::map<UUID, bool>& has_display_name_)
        {
            has_display_name = has_display_name_;
        }

        void SetDisplayName(const std::map<UUID, Chat>& display_name_)
        {
            display_name = display_name_;
        }

        void SetRemoved(const std::vector<UUID>& removed_)
        {
            removed = removed_;
        }

        const int GetAction() const
        {
            return action;
        }

        const std::map<UUID, PlayerInformation>& GetPlayers() const
        {
            return players;
        }

        const std::map<UUID, int>& GetGamemode() const
        {
            return gamemode;
        }

        const std::map<UUID, int>& GetPing() const
        {
            return ping;
        }

        const std::map<UUID, bool>& GetHasDisplayName() const
        {
            return has_display_name;
        }

        const std::map<UUID, Chat>& GetDisplayName() const
        {
            return display_name;
        }

        const std::vector<UUID>& GetRemoved() const
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
                UUID uuid = ReadUUID(iter, length);
                switch ((PlayerInfoAction)action)
                {
                case PlayerInfoAction::AddPlayer:
                {
                    players[uuid].Read(iter, length);
                }
                    break;
                case PlayerInfoAction::UpdateGamemode:
                    gamemode[uuid] = ReadVarInt(iter, length);
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
            WriteVarInt(action, container);
            switch ((PlayerInfoAction)action)
            {
            case PlayerInfoAction::AddPlayer:
                WriteVarInt(players.size(), container);
                for (auto it = players.begin(); it != players.end(); ++it)
                {
                    WriteUUID(it->first, container);
                    it->second.Write(container);
                }
                break;
            case PlayerInfoAction::UpdateGamemode:
                WriteVarInt(gamemode.size(), container);
                for (auto it = gamemode.begin(); it != gamemode.end(); ++it)
                {
                    WriteUUID(it->first, container);
                    WriteVarInt((int)it->second, container);
                }
                break;
            case PlayerInfoAction::UpdateLatency:
                WriteVarInt(ping.size(), container);
                for (auto it = ping.begin(); it != ping.end(); ++it)
                {
                    WriteUUID(it->first, container);
                    WriteVarInt((int)it->second, container);
                }
                break;
            case PlayerInfoAction::UpdateDisplayName:
                WriteVarInt(has_display_name.size(), container);
                for (auto it = has_display_name.begin(); it != has_display_name.end(); ++it)
                {
                    WriteUUID(it->first, container);
                    WriteData<bool>(it->second, container);
                    if (it->second)
                    {
                        display_name.at(it->first).Write(container);
                    }
                }
                break;
            case PlayerInfoAction::RemovePlayer:
                WriteVarInt(removed.size(), container);
                for (int i = 0; i < removed.size(); ++i)
                {
                    WriteUUID(removed[i], container);
                }
                break;
            default:
                break;
            }
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
                    picojson::value value2(picojson::object_type, false);
                    picojson::object& object2 = value2.get<picojson::object>();
                    object2["uuid"] = picojson::value(it->first);
                    object2["player_info"] = it->second.Serialize();
                    array.push_back(value2);
                }
                break;
            case PlayerInfoAction::UpdateGamemode:
                array.reserve(gamemode.size());
                for (auto it = gamemode.begin(); it != gamemode.end(); ++it)
                {
                    picojson::value value2(picojson::object_type, false);
                    picojson::object& object2 = value2.get<picojson::object>();
                    object2["uuid"] = picojson::value(it->first);
                    object2["gamemode"] = picojson::value((double)it->second);
                    array.push_back(value2);
                }
                break;
            case PlayerInfoAction::UpdateLatency:
                array.reserve(ping.size());
                for (auto it = ping.begin(); it != ping.end(); ++it)
                {
                    picojson::value value2(picojson::object_type, false);
                    picojson::object& object2 = value2.get<picojson::object>();
                    object2["uuid"] = picojson::value(it->first);
                    object2["ping"] = picojson::value((double)it->second);
                    array.push_back(value2);
                }
                break;
            case PlayerInfoAction::UpdateDisplayName:
                array.reserve(has_display_name.size());
                for (auto it = has_display_name.begin(); it != has_display_name.end(); ++it)
                {
                    picojson::value value2(picojson::object_type, false);
                    picojson::object& object2 = value2.get<picojson::object>();
                    object2["uuid"] = picojson::value(it->first);
                    object2["has_display_name"] = picojson::value(it->second);
                    if (it->second)
                    {
                        object2["display_name"] = display_name.at(it->first).Serialize();
                    }
                    array.push_back(value2);
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
        std::map<UUID, PlayerInformation> players;
        std::map<UUID, int> gamemode;
        std::map<UUID, int> ping;
        std::map<UUID, bool> has_display_name;
        std::map<UUID, Chat> display_name;
        std::vector<UUID> removed;
    };
} //ProtocolCraft