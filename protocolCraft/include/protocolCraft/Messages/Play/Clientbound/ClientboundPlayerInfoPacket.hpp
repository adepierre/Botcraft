#pragma once

#include <string>
#include <map>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"
#include "protocolCraft/Types/PlayerUpdate.hpp"
#include "protocolCraft/enums.hpp"

namespace ProtocolCraft
{
    enum class PlayerInfoAction
    {
        AddPlayer = 0,
        UpdateGameMode = 1,
        UpdateLatency = 2,
        UpdateDisplayName = 3,
        RemovePlayer = 4
    };

    class ClientboundPlayerInfoPacket : public BaseMessage<ClientboundPlayerInfoPacket>
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
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x32;
#elif PROTOCOL_VERSION == 755 // 1.17
            return 0x36;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Info";
        }

        virtual ~ClientboundPlayerInfoPacket() override
        {

        }

        void SetAction(const PlayerInfoAction action_)
        {
            action = action_;
        }

        void SetEntries(const std::map<UUID, PlayerUpdate>& entries_)
        {
            entries = entries_;
        }

        const PlayerInfoAction GetAction() const
        {
            return action;
        }

        const std::map<UUID, PlayerUpdate>& GetEntries() const
        {
            return entries;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            action = (PlayerInfoAction)ReadVarInt(iter, length);
            const int number_of_entries = ReadVarInt(iter, length);
            for (int i = 0; i < number_of_entries; ++i)
            {
                UUID uuid = ReadUUID(iter, length);
                switch (action)
                {
                case PlayerInfoAction::AddPlayer:
                {
                    entries[uuid].Read(iter, length);
                }
                    break;
                case PlayerInfoAction::UpdateGameMode:
                    entries[uuid].SetGameMode(ReadVarInt(iter, length));
                    break;
                case PlayerInfoAction::UpdateLatency:
                    entries[uuid].SetLatency(ReadVarInt(iter, length));
                    break;
                case PlayerInfoAction::UpdateDisplayName:
                {
                    const bool has_display_name = ReadData<bool>(iter, length);
                    if (has_display_name)
                    {
                        Chat display_name;
                        display_name.Read(iter, length);
                        entries[uuid].SetDisplayName(display_name);
                    }
                    break;
                }
                case PlayerInfoAction::RemovePlayer:
                    entries[uuid] = PlayerUpdate();
                    break;
                default:
                    break;
                }
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt((int)action, container);
            switch (action)
            {
            case PlayerInfoAction::AddPlayer:
                WriteVarInt(entries.size(), container);
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    WriteUUID(it->first, container);
                    it->second.Write(container);
                }
                break;
            case PlayerInfoAction::UpdateGameMode:
                WriteVarInt(entries.size(), container);
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    WriteUUID(it->first, container);
                    WriteVarInt((int)it->second.GetGameMode(), container);
                }
                break;
            case PlayerInfoAction::UpdateLatency:
                WriteVarInt(entries.size(), container);
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    WriteUUID(it->first, container);
                    WriteVarInt((int)it->second.GetLatency(), container);
                }
                break;
            case PlayerInfoAction::UpdateDisplayName:
                WriteVarInt(entries.size(), container);
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    WriteUUID(it->first, container);
                    WriteData<bool>(!it->second.GetDisplayName().GetText().empty(), container);
                    if (!it->second.GetDisplayName().GetText().empty())
                    {
                        it->second.GetDisplayName().Write(container);
                    }
                }
                break;
            case PlayerInfoAction::RemovePlayer:
                WriteVarInt(entries.size(), container);
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    WriteUUID(it->first, container);
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
            object["entries"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["entries"].get<picojson::array>();

            switch (action)
            {
            case PlayerInfoAction::AddPlayer:
                array.reserve(entries.size());
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    picojson::value value2(picojson::object_type, false);
                    picojson::object& object2 = value2.get<picojson::object>();
                    object2["uuid"] = picojson::value(it->first);
                    object2["player_info"] = it->second.Serialize();
                    array.push_back(value2);
                }
                break;
            case PlayerInfoAction::UpdateGameMode:
                array.reserve(entries.size());
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    picojson::value value2(picojson::object_type, false);
                    picojson::object& object2 = value2.get<picojson::object>();
                    object2["uuid"] = picojson::value(it->first);
                    object2["game_mode"] = picojson::value((double)it->second.GetGameMode());
                    array.push_back(value2);
                }
                break;
            case PlayerInfoAction::UpdateLatency:
                array.reserve(entries.size());
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    picojson::value value2(picojson::object_type, false);
                    picojson::object& object2 = value2.get<picojson::object>();
                    object2["uuid"] = picojson::value(it->first);
                    object2["latency"] = picojson::value((double)it->second.GetLatency());
                    array.push_back(value2);
                }
                break;
            case PlayerInfoAction::UpdateDisplayName:
                array.reserve(entries.size());
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    picojson::value value2(picojson::object_type, false);
                    picojson::object& object2 = value2.get<picojson::object>();
                    object2["uuid"] = picojson::value(it->first);
                    if (!it->second.GetDisplayName().GetText().empty())
                    {
                        object2["display_name"] = it->second.GetDisplayName().Serialize();
                    }
                    array.push_back(value2);
                }
                break;
            case PlayerInfoAction::RemovePlayer:
                array.reserve(entries.size());
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    array.push_back(picojson::value(it->first));
                }
                break;
            default:
                break;
            }

            return value;
        }

    private:
        PlayerInfoAction action;
        std::map<UUID, PlayerUpdate> entries;
    };
} //ProtocolCraft