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
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x36;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
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
            action = (PlayerInfoAction)(int)ReadData<VarInt>(iter, length);
            const int number_of_entries = ReadData<VarInt>(iter, length);
            for (int i = 0; i < number_of_entries; ++i)
            {
                UUID uuid = ReadData<UUID>(iter, length);
                switch (action)
                {
                case PlayerInfoAction::AddPlayer:
                {
                    entries[uuid].Read(iter, length);
                }
                    break;
                case PlayerInfoAction::UpdateGameMode:
                    entries[uuid].SetGameMode(ReadData<VarInt>(iter, length));
                    break;
                case PlayerInfoAction::UpdateLatency:
                    entries[uuid].SetLatency(ReadData<VarInt>(iter, length));
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
            WriteData<VarInt>((int)action, container);
            switch (action)
            {
            case PlayerInfoAction::AddPlayer:
                WriteData<VarInt>(entries.size(), container);
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    WriteData<UUID>(it->first, container);
                    it->second.Write(container);
                }
                break;
            case PlayerInfoAction::UpdateGameMode:
                WriteData<VarInt>(entries.size(), container);
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    WriteData<UUID>(it->first, container);
                    WriteData<VarInt>((int)it->second.GetGameMode(), container);
                }
                break;
            case PlayerInfoAction::UpdateLatency:
                WriteData<VarInt>(entries.size(), container);
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    WriteData<UUID>(it->first, container);
                    WriteData<VarInt>((int)it->second.GetLatency(), container);
                }
                break;
            case PlayerInfoAction::UpdateDisplayName:
                WriteData<VarInt>(entries.size(), container);
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    WriteData<UUID>(it->first, container);
                    WriteData<bool>(!it->second.GetDisplayName().GetText().empty(), container);
                    if (!it->second.GetDisplayName().GetText().empty())
                    {
                        it->second.GetDisplayName().Write(container);
                    }
                }
                break;
            case PlayerInfoAction::RemovePlayer:
                WriteData<VarInt>(entries.size(), container);
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    WriteData<UUID>(it->first, container);
                }
                break;
            default:
                break;
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["action"] = action;
            output["entries"] = nlohmann::json::array();

            switch (action)
            {
            case PlayerInfoAction::AddPlayer:
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    nlohmann::json entry;
                    entry["uuid"] = it->first;
                    entry["player_info"] = it->second.Serialize();
                    output["entries"].push_back(entry);
                }
                break;
            case PlayerInfoAction::UpdateGameMode:
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    nlohmann::json entry;
                    entry["uuid"] = it->first;
                    entry["game_mode"] = it->second.GetGameMode();
                    output["entries"].push_back(entry);
                }
                break;
            case PlayerInfoAction::UpdateLatency:
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    nlohmann::json entry;
                    entry["uuid"] = it->first;
                    entry["latency"] = it->second.GetLatency();
                    output["entries"].push_back(entry);
                }
                break;
            case PlayerInfoAction::UpdateDisplayName:
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    nlohmann::json entry;
                    entry["uuid"] = it->first;
                    if (!it->second.GetDisplayName().GetText().empty())
                    {
                        entry["display_name"] = it->second.GetDisplayName().Serialize();
                    }
                    output["entries"].push_back(entry);
                }
                break;
            case PlayerInfoAction::RemovePlayer:
                for (auto it = entries.begin(); it != entries.end(); ++it)
                {
                    output["entries"].push_back(it->first);
                }
                break;
            default:
                break;
            }

            return output;
        }

    private:
        PlayerInfoAction action;
        std::map<UUID, PlayerUpdate> entries;
    };
} //ProtocolCraft