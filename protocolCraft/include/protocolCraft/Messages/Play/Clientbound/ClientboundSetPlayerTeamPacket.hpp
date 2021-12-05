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
#elif PROTOCOL_VERSION == 757 // 1.18
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
            name_ = ReadData<std::string>(iter, length);
            method = ReadData<char>(iter, length);
            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 375
                display_name = ReadData<std::string>(iter, length);
                player_prefix = ReadData<std::string>(iter, length);
                player_suffix = ReadData<std::string>(iter, length);
                options = ReadData<char>(iter, length);
                nametag_visibility = ReadData<std::string>(iter, length);
                collision_rule = ReadData<std::string>(iter, length);
                color = ReadData<char>(iter, length);
#else
                display_name.Read(iter, length);
                options = ReadData<char>(iter, length);
                nametag_visibility = ReadData<std::string>(iter, length);
                collision_rule = ReadData<std::string>(iter, length);
                color = ReadData<VarInt>(iter, length);
                player_prefix.Read(iter, length);
                player_suffix.Read(iter, length);
#endif
            }
            
            if (method == 0 || method == 3 || method == 4)
            {
                int players_count = ReadData<VarInt>(iter, length);
                players = std::vector<std::string>(players_count);
                for (int i = 0; i < players_count; ++i)
                {
                    players[i] = ReadData<std::string>(iter, length);
                }
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(name_, container);
            WriteData<char>(method, container);

            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 375
                WriteData<std::string>(display_name, container);
                WriteData<std::string>(player_prefix, container);
                WriteData<std::string>(player_suffix, container);
                WriteData<char>(options, container);
                WriteData<std::string>(nametag_visibility, container);
                WriteData<std::string>(collision_rule, container);
                WriteData<char>(color, container);
#else
                display_name.Write(container);
                WriteData<char>(options, container);
                WriteData<std::string>(nametag_visibility, container);
                WriteData<std::string>(collision_rule, container);
                WriteData<VarInt>(color, container);
                player_prefix.Write(container);
                player_suffix.Write(container);
#endif
            }
            
            if (method == 0 || method == 3 || method == 4)
            {
                WriteData<VarInt>(players.size(), container);
                for (int i = 0; i < players.size(); ++i)
                {
                    WriteData<std::string>(players[i], container);
                }
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["name_"] = name_;
            output["method"] = method;

            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 375
                output["display_name"] = display_name;
                output["player_prefix"] = player_prefix;
                output["player_suffix"] = player_suffix;
                output["options"] = options;
                output["nametag_visibility"] = nametag_visibility;
                output["collision_rule"] = collision_rule;
                output["color"] = color;
#else
                output["display_name"] = display_name.Serialize();
                output["options"] = options;
                output["nametag_visibility"] = nametag_visibility;
                output["collision_rule"] = collision_rule;
                output["color"] = color;
                output["player_prefix"] = player_prefix.Serialize();
                output["player_suffix"] = player_suffix.Serialize();
#endif
            }

            if (method == 0 || method == 3 || method == 4)
            {
                output["players"] = players;
            }

            return output;
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