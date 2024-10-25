#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include <string>
#include <map>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/PlayerUpdate.hpp"
#include "protocolCraft/Utilities/CustomType.hpp"

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
        static constexpr std::string_view packet_name = "Player Info";

    private:
        std::map<UUID, PlayerUpdate> ReadEntries(ReadIterator& iter, size_t& length) const
        {
            std::map<UUID, PlayerUpdate> entries;
            switch (GetAction())
            {
            case PlayerInfoAction::AddPlayer:
                entries = ReadData<std::map<UUID, PlayerUpdate>>(iter, length);
                break;
            case PlayerInfoAction::UpdateGameMode:
            {
                const int map_size = ReadData<VarInt>(iter, length);
                for (int i = 0; i < map_size; ++i)
                {
                    const UUID uuid = ReadData<UUID>(iter, length);
                    const int game_mode = ReadData<VarInt>(iter, length);
                    entries[uuid].SetGameMode(game_mode);
                }
                break;
            }
            case PlayerInfoAction::UpdateLatency:
            {
                const int map_size = ReadData<VarInt>(iter, length);
                for (int i = 0; i < map_size; ++i)
                {
                    const UUID uuid = ReadData<UUID>(iter, length);
                    const int latency = ReadData<VarInt>(iter, length);
                    entries[uuid].SetLatency(latency);
                }
                break;
            }
            case PlayerInfoAction::UpdateDisplayName:
            {
                const int map_size = ReadData<VarInt>(iter, length);
                for (int i = 0; i < map_size; ++i)
                {
                    const UUID uuid = ReadData<UUID>(iter, length);
                    const std::optional<Chat> display_name = ReadData<std::optional<Chat>>(iter, length);
                    entries[uuid].SetDisplayName(display_name);
                }
                break;
            }
            case PlayerInfoAction::RemovePlayer:
            {
                const int map_size = ReadData<VarInt>(iter, length);
                for (int i = 0; i < map_size; ++i)
                {
                    const UUID uuid = ReadData<UUID>(iter, length);
                    entries[uuid] = PlayerUpdate();
                }
                break;
            }
            default:
                break;
            }
            return entries;
        }

        void WriteEntries(const std::map<UUID, PlayerUpdate>& entries, WriteContainer& container) const
        {
            switch (GetAction())
            {
            case PlayerInfoAction::AddPlayer:
                WriteData<std::map<UUID, PlayerUpdate>>(entries, container);
                break;
            case PlayerInfoAction::UpdateGameMode:
                WriteData<VarInt>(static_cast<int>(entries.size()), container);
                for (const auto& [uuid, player_update] : entries)
                {
                    WriteData<UUID>(uuid, container);
                    WriteData<VarInt>(player_update.GetGameMode(), container);
                }
                break;
            case PlayerInfoAction::UpdateLatency:
                WriteData<VarInt>(static_cast<int>(entries.size()), container);
                for (const auto& [uuid, player_update] : entries)
                {
                    WriteData<UUID>(uuid, container);
                    WriteData<VarInt>(player_update.GetLatency(), container);
                }
                break;
            case PlayerInfoAction::UpdateDisplayName:
                WriteData<VarInt>(static_cast<int>(entries.size()), container);
                for (const auto& [uuid, player_update] : entries)
                {
                    WriteData<UUID>(uuid, container);
                    WriteData<std::optional<Chat>>(player_update.GetDisplayName(), container);
                }
                break;
            case PlayerInfoAction::RemovePlayer:
                WriteData<VarInt>(static_cast<int>(entries.size()), container);
                for (const auto& [uuid, player_update] : entries)
                {
                    WriteData<UUID>(uuid, container);
                }
                break;
            default:
                break;
            }
        }

        std::optional<Json::Value> SerializeEntries(const std::map<UUID, PlayerUpdate>& entries) const
        {
            Json::Array output;
            switch (GetAction())
            {
            case PlayerInfoAction::AddPlayer:
                for (const auto& p : entries)
                {
                    output.push_back({ {"uuid", p.first}, {"player_info", p.second} });
                }
                break;
            case PlayerInfoAction::UpdateGameMode:
                for (const auto& p : entries)
                {
                    output.push_back({ {"uuid", p.first}, {"game_mode", p.second.GetGameMode()} });
                }
                break;
            case PlayerInfoAction::UpdateLatency:
                for (const auto& p : entries)
                {
                    output.push_back({ {"uuid", p.first}, {"latency", p.second.GetLatency()} });
                }
                break;
            case PlayerInfoAction::UpdateDisplayName:
                for (const auto& p : entries)
                {
                    Json::Value entry;
                    entry["uuid"] = p.first;
                    if (p.second.GetDisplayName().has_value())
                    {
                        entry["display_name"] = p.second.GetDisplayName().value().Serialize();
                    }
                    output.push_back(entry);
                }
                break;
            case PlayerInfoAction::RemovePlayer:
                for (const auto& p : entries)
                {
                    output.push_back(p.first);
                }
                break;
            default:
                break;
            }

            return output;
        }

        SERIALIZED_FIELD(Action, Internal::DiffType<PlayerInfoAction, VarInt>);
        SERIALIZED_FIELD(Entries, Internal::CustomType<std::map<UUID, PlayerUpdate>, &THIS::ReadEntries, &THIS::WriteEntries, &THIS::SerializeEntries>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
