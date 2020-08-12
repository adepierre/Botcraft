#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 374
#include "protocolCraft/Types/Chat.hpp"
#endif

namespace ProtocolCraft
{
    enum class TeamsMode
    {
        CreateTeam = 0,
        RemoveTeam = 1,
        UpdateTeamInfo = 2,
        AddPlayersToTeam = 3,
        RemovePlayersFromTeam = 4
    };

    class Teams : public BaseMessage<Teams>
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
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x4C;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Teams";
        }

        void SetTeamName(const std::string& team_name_)
        {
            team_name = team_name_;
        }

        void SetMode(const char mode_)
        {
            mode = mode_;
        }

#if PROTOCOL_VERSION < 375
        void SetTeamDisplayName(const std::string& team_display_name_)
#else
        void SetTeamDisplayName(const Chat& team_display_name_)
#endif
        {
            team_display_name = team_display_name_;
        }

        void SetFriendlyFlags(const char friendly_flags_)
        {
            friendly_flags = friendly_flags_;
        }

        void SetNameTagVisibility(const std::string& name_tag_visibility_)
        {
            name_tag_visibility = name_tag_visibility_;
        }

        void SetCollisionRule(const std::string& collision_rule_)
        {
            collision_rule = collision_rule_;
        }

        void SetTeamColor(const int team_color_)
        {
            team_color = team_color_;
        }

#if PROTOCOL_VERSION < 375
        void SetTeamPrefix(const std::string& team_prefix_)
#else
        void SetTeamPrefix(const Chat& team_prefix_)
#endif
        {
            team_prefix = team_prefix_;
        }

#if PROTOCOL_VERSION < 375
        void SetTeamSuffix(const std::string& team_suffix_)
#else
        void SetTeamSuffix(const Chat& team_suffix_)
#endif
        {
            team_suffix = team_suffix_;
        }

        void SetEntityCount(const int entity_count_)
        {
            entity_count = entity_count_;
        }

        void SetEntities(const std::vector<std::string>& entities_)
        {
            entities = entities_;
        }


        const std::string& GetTeamName() const
        {
            return team_name;
        }

        const char GetMode() const
        {
            return mode;
        }

#if PROTOCOL_VERSION < 375
        const std::string& GetTeamDisplayName() const
#else
        const Chat& GetTeamDisplayName() const
#endif
        {
            return team_display_name;
        }

        const char GetFriendlyFlags() const
        {
            return friendly_flags;
        }

        const std::string& GetNameTagVisibility() const
        {
            return name_tag_visibility;
        }

        const std::string& GetCollisionRule() const
        {
            return collision_rule;
        }

        const int GetTeamColor() const
        {
            return team_color;
        }

#if PROTOCOL_VERSION < 375
        const std::string& GetTeamPrefix() const
#else
        const Chat& GetTeamPrefix() const
#endif
        {
            return team_prefix;
        }

#if PROTOCOL_VERSION < 375
        const std::string& GetTeamSuffix() const
#else
        const Chat& GetTeamSuffix() const
#endif
        {
            return team_suffix;
        }

        const int GetEntityCount() const
        {
            return entity_count;
        }

        const std::vector<std::string>& GetEntities() const
        {
            return entities;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            team_name = ReadString(iter, length);
            mode = ReadData<char>(iter, length);
            switch ((TeamsMode)mode)
            {
            case TeamsMode::CreateTeam:
#if PROTOCOL_VERSION < 375
                team_display_name = ReadString(iter, length);
                team_prefix = ReadString(iter, length);
                team_suffix = ReadString(iter, length);
                friendly_flags = ReadData<char>(iter, length);
                name_tag_visibility = ReadString(iter, length);
                collision_rule = ReadString(iter, length);
                team_color = ReadData<char>(iter, length);
                entity_count = ReadVarInt(iter, length);
                entities = std::vector<std::string>(entity_count);
                for (int i = 0; i < entity_count; ++i)
                {
                    entities[i] = ReadString(iter, length);
                }
#else
                team_display_name.Read(iter, length);
                friendly_flags = ReadData<char>(iter, length);
                name_tag_visibility = ReadString(iter, length);
                collision_rule = ReadString(iter, length);
                team_color = ReadVarInt(iter, length);
                team_prefix.Read(iter, length);
                team_suffix.Read(iter, length);
                entity_count = ReadVarInt(iter, length);
                entities = std::vector<std::string>(entity_count);
                for (int i = 0; i < entity_count; ++i)
                {
                    entities[i] = ReadString(iter, length);
                }
#endif
                break;
            case TeamsMode::RemoveTeam:

                break;
            case TeamsMode::UpdateTeamInfo:
#if PROTOCOL_VERSION < 375
                team_display_name = ReadString(iter, length);
                team_prefix = ReadString(iter, length);
                team_suffix = ReadString(iter, length);
                friendly_flags = ReadData<char>(iter, length);
                name_tag_visibility = ReadString(iter, length);
                collision_rule = ReadString(iter, length);
                team_color = ReadData<char>(iter, length);
#else
                team_display_name.Read(iter, length);
                friendly_flags = ReadData<char>(iter, length);
                name_tag_visibility = ReadString(iter, length);
                collision_rule = ReadString(iter, length);
                team_color = ReadVarInt(iter, length);
                team_prefix.Read(iter, length);
                team_suffix.Read(iter, length);
#endif
                break;
            case TeamsMode::AddPlayersToTeam:
                entity_count = ReadVarInt(iter, length);
                entities = std::vector<std::string>(entity_count);
                for (int i = 0; i < entity_count; ++i)
                {
                    entities[i] = ReadString(iter, length);
                }
                break;
            case TeamsMode::RemovePlayersFromTeam:
                entity_count = ReadVarInt(iter, length);
                entities = std::vector<std::string>(entity_count);
                for (int i = 0; i < entity_count; ++i)
                {
                    entities[i] = ReadString(iter, length);
                }
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(team_name, container);
            WriteData<char>(mode, container);
            switch ((TeamsMode)mode)
            {
            case TeamsMode::CreateTeam:
#if PROTOCOL_VERSION < 375
                WriteString(team_display_name, container);
                WriteString(team_prefix, container);
                WriteString(team_suffix, container);
                WriteData<char>(friendly_flags, container);
                WriteString(name_tag_visibility, container);
                WriteString(collision_rule, container);
                WriteData<char>(team_color, container);
                WriteVarInt(entity_count, container);
                for (int i = 0; i < entity_count; ++i)
                {
                    WriteString(entities[i], container);
                }
#else
                team_display_name.Write(container);
                WriteData<char>(friendly_flags, container);
                WriteString(name_tag_visibility, container);
                WriteString(collision_rule, container);
                WriteVarInt(team_color, container);
                team_prefix.Write(container);
                team_suffix.Write(container);
                WriteVarInt(entity_count, container);
                for (int i = 0; i < entity_count; ++i)
                {
                    WriteString(entities[i], container);
                }
#endif
                break;
            case TeamsMode::RemoveTeam:

                break;
            case TeamsMode::UpdateTeamInfo:
#if PROTOCOL_VERSION < 375
                WriteString(team_display_name, container);
                WriteString(team_prefix, container);
                WriteString(team_suffix, container);
                WriteData<char>(friendly_flags, container);
                WriteString(name_tag_visibility, container);
                WriteString(collision_rule, container);
                WriteData<char>(team_color, container);
#else
                team_display_name.Write(container);
                WriteData<char>(friendly_flags, container);
                WriteString(name_tag_visibility, container);
                WriteString(collision_rule, container);
                WriteVarInt(team_color, container);
                team_prefix.Write(container);
                team_suffix.Write(container);
#endif
                break;
            case TeamsMode::AddPlayersToTeam:
                WriteVarInt(entity_count, container);
                for (int i = 0; i < entity_count; ++i)
                {
                    WriteString(entities[i], container);
                }
                break;
            case TeamsMode::RemovePlayersFromTeam:
                WriteVarInt(entity_count, container);
                for (int i = 0; i < entity_count; ++i)
                {
                    WriteString(entities[i], container);
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

            object["team_name"] = picojson::value(team_name);
            object["mode"] = picojson::value((double)mode);
            switch ((TeamsMode)mode)
            {
            case TeamsMode::CreateTeam:
            {
#if PROTOCOL_VERSION < 375
                object["team_display_name"] = picojson::value(team_display_name);
                object["team_prefix"] = picojson::value(team_prefix);
                object["team_suffix"] = picojson::value(team_suffix);
                object["friendly_flags"] = picojson::value((double)friendly_flags);
                object["name_tag_visibility"] = picojson::value(name_tag_visibility);
                object["collision_rule"] = picojson::value(collision_rule);
                object["team_color"] = picojson::value((double)team_color);
                object["entity_count"] = picojson::value((double)entity_count);
                object["entities"] = picojson::value(picojson::array_type, false);
                picojson::array& array = object["entities"].get<picojson::array>();
                for (int i = 0; i < entity_count; ++i)
                {
                    array.push_back(picojson::value(entities[i]));
                }
#else
                object["team_display_name"] = team_display_name.Serialize();
                object["friendly_flags"] = picojson::value((double)friendly_flags);
                object["name_tag_visibility"] = picojson::value(name_tag_visibility);
                object["collision_rule"] = picojson::value(collision_rule);
                object["team_color"] = picojson::value((double)team_color);
                object["team_prefix"] = team_prefix.Serialize();
                object["team_suffix"] = team_suffix.Serialize();
                object["entity_count"] = picojson::value((double)entity_count);
                object["entities"] = picojson::value(picojson::array_type, false);
                picojson::array& array = object["entities"].get<picojson::array>();
                for (int i = 0; i < entity_count; ++i)
                {
                    array.push_back(picojson::value(entities[i]));
                }
#endif
                break;
            }
            case TeamsMode::RemoveTeam:

                break;
            case TeamsMode::UpdateTeamInfo:
#if PROTOCOL_VERSION < 375
                object["team_display_name"] = picojson::value(team_display_name);
                object["team_prefix"] = picojson::value(team_prefix);
                object["team_suffix"] = picojson::value(team_suffix);
                object["friendly_flags"] = picojson::value((double)friendly_flags);
                object["name_tag_visibility"] = picojson::value(name_tag_visibility);
                object["collision_rule"] = picojson::value(collision_rule);
                object["team_color"] = picojson::value((double)team_color);
#else
                object["team_display_name"] = team_display_name.Serialize();
                object["friendly_flags"] = picojson::value((double)friendly_flags);
                object["name_tag_visibility"] = picojson::value(name_tag_visibility);
                object["collision_rule"] = picojson::value(collision_rule);
                object["team_color"] = picojson::value((double)team_color);
                object["team_prefix"] = team_prefix.Serialize();
                object["team_suffix"] = team_suffix.Serialize();
#endif
                break;
            case TeamsMode::AddPlayersToTeam:
            {
                object["entity_count"] = picojson::value((double)entity_count);
                object["entities"] = picojson::value(picojson::array_type, false);
                picojson::array& array = object["entities"].get<picojson::array>();
                for (int i = 0; i < entity_count; ++i)
                {
                    array.push_back(picojson::value(entities[i]));
                }
                break;
            }
            case TeamsMode::RemovePlayersFromTeam:
            {
                object["entity_count"] = picojson::value((double)entity_count);
                object["entities"] = picojson::value(picojson::array_type, false);
                picojson::array& array = object["entities"].get<picojson::array>();
                for (int i = 0; i < entity_count; ++i)
                {
                    array.push_back(picojson::value(entities[i]));
                }
                break;
            }
            default:
                break;
            }

            return value;
        }

    private:
        std::string team_name;
        char mode;
#if PROTOCOL_VERSION < 375
        std::string team_display_name;
#else
        Chat team_display_name;
#endif
        char friendly_flags;
        std::string name_tag_visibility;
        std::string collision_rule;
#if PROTOCOL_VERSION < 375
        char team_color;
#else
        int team_color;
#endif
#if PROTOCOL_VERSION < 375
        std::string team_prefix;
        std::string team_suffix;
#else
        Chat team_prefix;
        Chat team_suffix;
#endif
        int entity_count;
        std::vector<std::string> entities;

    };
} //ProtocolCraft