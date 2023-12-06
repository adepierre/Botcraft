#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 374 /* > 1.12.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSetPlayerTeamPacket : public BaseMessage<ClientboundSetPlayerTeamPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x47;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x4B;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */ || PROTOCOL_VERSION == 735 /* 1.16 */ ||  \
      PROTOCOL_VERSION == 736 /* 1.16.1 */ || PROTOCOL_VERSION == 751 /* 1.16.2 */ ||  \
      PROTOCOL_VERSION == 753 /* 1.16.3 */ || PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x55;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x5C;
#elif PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x5E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Player Team";

        virtual ~ClientboundSetPlayerTeamPacket() override
        {

        }

        void SetName_(const std::string& name__)
        {
            name_ = name__;
        }

#if PROTOCOL_VERSION < 375 /* < 1.13 */
        void SetDisplayName(const std::string& display_name_)
#else
        void SetDisplayName(const Chat& display_name_)
#endif
        {
            display_name = display_name_;
        }

#if PROTOCOL_VERSION < 375 /* < 1.13 */
        void SetPlayerPrefix(const std::string& player_prefix_)
#else
        void SetPlayerPrefix(const Chat& player_prefix_)
#endif
        {
            player_prefix = player_prefix_;
        }

#if PROTOCOL_VERSION < 375 /* < 1.13 */
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

#if PROTOCOL_VERSION < 375 /* < 1.13 */
        const std::string& GetDisplayName() const
#else
        const Chat& GetDisplayName() const
#endif
        {
            return display_name;
        }

#if PROTOCOL_VERSION < 375 /* < 1.13 */
        const std::string& GetPlayerPrefix() const
#else
        const Chat& GetPlayerPrefix() const
#endif
        {
            return player_prefix;
        }

#if PROTOCOL_VERSION < 375 /* < 1.13 */
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

        int GetColor() const
        {
            return color;
        }

        const std::vector<std::string>& GetPlayers() const
        {
            return players;
        }

        char GetMethod() const
        {
            return method;
        }

        char GetOptions() const
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
#if PROTOCOL_VERSION < 375 /* < 1.13 */
                display_name = ReadData<std::string>(iter, length);
                player_prefix = ReadData<std::string>(iter, length);
                player_suffix = ReadData<std::string>(iter, length);
                options = ReadData<char>(iter, length);
                nametag_visibility = ReadData<std::string>(iter, length);
                collision_rule = ReadData<std::string>(iter, length);
                color = ReadData<char>(iter, length);
#else
                display_name = ReadData<Chat>(iter, length);
                options = ReadData<char>(iter, length);
                nametag_visibility = ReadData<std::string>(iter, length);
                collision_rule = ReadData<std::string>(iter, length);
                color = ReadData<VarInt>(iter, length);
                player_prefix = ReadData<Chat>(iter, length);
                player_suffix = ReadData<Chat>(iter, length);
#endif
            }
            
            if (method == 0 || method == 3 || method == 4)
            {
                players = ReadVector<std::string>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(name_, container);
            WriteData<char>(method, container);

            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 375 /* < 1.13 */
                WriteData<std::string>(display_name, container);
                WriteData<std::string>(player_prefix, container);
                WriteData<std::string>(player_suffix, container);
                WriteData<char>(options, container);
                WriteData<std::string>(nametag_visibility, container);
                WriteData<std::string>(collision_rule, container);
                WriteData<char>(color, container);
#else
                WriteData<Chat>(display_name, container);
                WriteData<char>(options, container);
                WriteData<std::string>(nametag_visibility, container);
                WriteData<std::string>(collision_rule, container);
                WriteData<VarInt>(color, container);
                WriteData<Chat>(player_prefix, container);
                WriteData<Chat>(player_suffix, container);
#endif
            }
            
            if (method == 0 || method == 3 || method == 4)
            {
                WriteVector<std::string>(players, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["name_"] = name_;
            output["method"] = method;

            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 375 /* < 1.13 */
                output["display_name"] = display_name;
                output["player_prefix"] = player_prefix;
                output["player_suffix"] = player_suffix;
                output["options"] = options;
                output["nametag_visibility"] = nametag_visibility;
                output["collision_rule"] = collision_rule;
                output["color"] = color;
#else
                output["display_name"] = display_name;
                output["options"] = options;
                output["nametag_visibility"] = nametag_visibility;
                output["collision_rule"] = collision_rule;
                output["color"] = color;
                output["player_prefix"] = player_prefix;
                output["player_suffix"] = player_suffix;
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
#if PROTOCOL_VERSION < 375 /* < 1.13 */
        std::string display_name;
#else
        Chat display_name;
#endif
#if PROTOCOL_VERSION < 375 /* < 1.13 */
        std::string player_prefix;
        std::string player_suffix;
#else
        Chat player_prefix;
        Chat player_suffix;
#endif
        std::string nametag_visibility;
        std::string collision_rule;
#if PROTOCOL_VERSION < 375 /* < 1.13 */
        char color = 0;
#else
        int color = 0;
#endif
        std::vector<std::string> players;
        char method = 0;
        char options = 0;

    };
} //ProtocolCraft
