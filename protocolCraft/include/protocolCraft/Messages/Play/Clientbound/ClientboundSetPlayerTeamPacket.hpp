#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 374
#include "protocolCraft/Types/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSetPlayerTeamPacket : public BaseMessage<ClientboundSetPlayerTeamPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x44;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x47;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x4B;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x4C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x4C;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x4C;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x55;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Player Team";
        }

        virtual ~ClientboundSetPlayerTeamPacket() override
        {

        }

        void SetName_(const std::string& name__)
        {
            name_ = name__;
        }

#if PROTOCOL_VERSION < 375
        void SetDisplayName(const std::string& display_name_)
#else
        void SetDisplayName(const Chat& display_name_)
#endif
        {
            display_name = display_name_;
        }

#if PROTOCOL_VERSION < 375
        void SetPlayerPrefix(const std::string& player_prefix_)
#else
        void SetPlayerPrefix(const Chat& player_prefix_)
#endif
        {
            player_prefix = player_prefix_;
        }

#if PROTOCOL_VERSION < 375
        void SetPlayerSuffix(const std::string& player_suffix_)
#else
        void SetPlayerSuffix(const Chat& player_suffix_)
#endif
        {
            player_suffix = player_suffix_;
        }

        void SetNametagVisibility(const std::string& nametag_visibility_)
        {
            nametag_visibility = nametag_visibility_;
        }

        void SetCollisionRule(const std::string& collision_rule_)
        {
            collision_rule = collision_rule_;
        }

        void SetColor(const int color_)
        {
            color = color_;
        }

        void SetPlayers(const std::vector<std::string>& players_)
        {
            players = players_;
        }

        void SetMethod(const char method_)
        {
            method = method_;
        }

        void SetOptions(const char options_)
        {
            options = options_;
        }


        const std::string& GetName_() const
        {
            return name_;
        }

#if PROTOCOL_VERSION < 375
        const std::string& GetDisplayName() const
#else
        const Chat& GetDisplayName() const
#endif
        {
            return display_name;
        }

#if PROTOCOL_VERSION < 375
        const std::string& GetPlayerPrefix() const
#else
        const Chat& GetPlayerPrefix() const
#endif
        {
            return player_prefix;
        }

#if PROTOCOL_VERSION < 375
        const std::string& GetPlayerSuffix() const
#else
        const Chat& GetPlayerSuffix() const
#endif
        {
            return player_suffix;
        }

        const std::string& GetNametagVisibility() const
        {
            return nametag_visibility;
        }

        const std::string& GetCollisionRule() const
        {
            return collision_rule;
        }

        const int GetColor() const
        {
            return color;
        }

        const std::vector<std::string>& GetPlayers() const
        {
            return players;
        }

        const char GetMethod() const
        {
            return method;
        }

        const char GetOptions() const
        {
            return options;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            name_ = ReadString(iter, length);
            method = ReadData<char>(iter, length);
            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 375
                display_name = ReadString(iter, length);
                player_prefix = ReadString(iter, length);
                player_suffix = ReadString(iter, length);
                options = ReadData<char>(iter, length);
                nametag_visibility = ReadString(iter, length);
                collision_rule = ReadString(iter, length);
                color = ReadData<char>(iter, length);
#else
                display_name.Read(iter, length);
                options = ReadData<char>(iter, length);
                nametag_visibility = ReadString(iter, length);
                collision_rule = ReadString(iter, length);
                color = ReadVarInt(iter, length);
                player_prefix.Read(iter, length);
                player_suffix.Read(iter, length);
#endif
            }
            
            if (method == 0 || method == 3 || method == 4)
            {
                int players_count = ReadVarInt(iter, length);
                players = std::vector<std::string>(players_count);
                for (int i = 0; i < players_count; ++i)
                {
                    players[i] = ReadString(iter, length);
                }
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(name_, container);
            WriteData<char>(method, container);

            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 375
                WriteString(display_name, container);
                WriteString(player_prefix, container);
                WriteString(player_suffix, container);
                WriteData<char>(options, container);
                WriteString(nametag_visibility, container);
                WriteString(collision_rule, container);
                WriteData<char>(color, container);
#else
                display_name.Write(container);
                WriteData<char>(options, container);
                WriteString(nametag_visibility, container);
                WriteString(collision_rule, container);
                WriteVarInt(color, container);
                player_prefix.Write(container);
                player_suffix.Write(container);
#endif
            }
            
            if (method == 0 || method == 3 || method == 4)
            {
                WriteVarInt(players.size(), container);
                for (int i = 0; i < players.size(); ++i)
                {
                    WriteString(players[i], container);
                }
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["name_"] = picojson::value(name_);
            object["method"] = picojson::value((double)method);

            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 375
                object["display_name"] = picojson::value(display_name);
                object["player_prefix"] = picojson::value(player_prefix);
                object["player_suffix"] = picojson::value(player_suffix);
                object["options"] = picojson::value((double)options);
                object["nametag_visibility"] = picojson::value(nametag_visibility);
                object["collision_rule"] = picojson::value(collision_rule);
                object["color"] = picojson::value((double)color);
#else
                object["display_name"] = display_name.Serialize();
                object["options"] = picojson::value((double)options);
                object["nametag_visibility"] = picojson::value(nametag_visibility);
                object["collision_rule"] = picojson::value(collision_rule);
                object["color"] = picojson::value((double)color);
                object["player_prefix"] = player_prefix.Serialize();
                object["player_suffix"] = player_suffix.Serialize();
#endif
            }

            if (method == 0 || method == 3 || method == 4)
            {
                object["players"] = picojson::value(picojson::array_type, false);
                picojson::array& array = object["players"].get<picojson::array>();
                for (int i = 0; i < players.size(); ++i)
                {
                    array.push_back(picojson::value(players[i]));
                }
            }

            return value;
        }

    private:
        std::string name_;
#if PROTOCOL_VERSION < 375
        std::string display_name;
#else
        Chat display_name;
#endif
#if PROTOCOL_VERSION < 375
        std::string player_prefix;
        std::string player_suffix;
#else
        Chat player_prefix;
        Chat player_suffix;
#endif
        std::string nametag_visibility;
        std::string collision_rule;
#if PROTOCOL_VERSION < 375
        char color;
#else
        int color;
#endif
        std::vector<std::string> players;
        char method;
        char options;

    };
} //ProtocolCraft