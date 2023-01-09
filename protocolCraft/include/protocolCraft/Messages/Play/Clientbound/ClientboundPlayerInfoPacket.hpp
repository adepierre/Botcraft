#if PROTOCOL_VERSION < 761
#pragma once

#include <string>
#include <map>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/PlayerUpdate.hpp"

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
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x32;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x37;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Player Info";

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

        PlayerInfoAction GetAction() const
        {
            return action;
        }

        const std::map<UUID, PlayerUpdate>& GetEntries() const
        {
            return entries;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            action = static_cast<PlayerInfoAction>(static_cast<int>(ReadData<VarInt>(iter, length)));
            switch (action)
            {
            case PlayerInfoAction::AddPlayer:
                entries = ReadMap<UUID, PlayerUpdate>(iter, length);
                break;
            case PlayerInfoAction::UpdateGameMode:
                entries = ReadMap<UUID, PlayerUpdate>(iter, length,
                    [](ReadIterator& i, size_t& l)
                    {
                        const UUID uuid = ReadData<UUID>(i, l);
                        PlayerUpdate player_update;
                        player_update.SetGameMode(ReadData<VarInt>(i, l));

                        return std::make_pair(uuid, player_update);
                    }
                );
                break;
            case PlayerInfoAction::UpdateLatency:
                entries = ReadMap<UUID, PlayerUpdate>(iter, length,
                    [](ReadIterator& i, size_t& l)
                    {
                        const UUID uuid = ReadData<UUID>(i, l);
                        PlayerUpdate player_update;
                        player_update.SetLatency(ReadData<VarInt>(i, l));

                        return std::make_pair(uuid, player_update);
                    }
                );
                break;
            case PlayerInfoAction::UpdateDisplayName:
                entries = ReadMap<UUID, PlayerUpdate>(iter, length,
                    [](ReadIterator& i, size_t& l)
                    {
                        const UUID uuid = ReadData<UUID>(i, l);
                        PlayerUpdate player_update;
                        player_update.SetDisplayName(ReadOptional<Chat>(i, l));

                        return std::make_pair(uuid, player_update);
                    }
                );
                break;
            case PlayerInfoAction::RemovePlayer:
                entries = ReadMap<UUID, PlayerUpdate>(iter, length,
                    [](ReadIterator& i, size_t& l)
                    {
                        const UUID uuid = ReadData<UUID>(i, l);

                        return std::make_pair(uuid, PlayerUpdate());
                    }
                );
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(static_cast<int>(action), container);
            switch (action)
            {
            case PlayerInfoAction::AddPlayer:
                WriteMap<UUID, PlayerUpdate>(entries, container);
                break;
            case PlayerInfoAction::UpdateGameMode:
                WriteMap<UUID, PlayerUpdate>(entries, container,
                    [](const std::pair<const UUID, PlayerUpdate>& p, WriteContainer& c)
                    {
                        WriteData<UUID>(p.first, c);
                        WriteData<VarInt>(static_cast<int>(p.second.GetGameMode()), c);
                    }
                );
                break;
            case PlayerInfoAction::UpdateLatency:
                WriteMap<UUID, PlayerUpdate>(entries, container,
                    [](const std::pair<const UUID, PlayerUpdate>& p, WriteContainer& c)
                    {
                        WriteData<UUID>(p.first, c);
                        WriteData<VarInt>(static_cast<int>(p.second.GetLatency()), c);
                    }
                );
                break;
            case PlayerInfoAction::UpdateDisplayName:
                WriteMap<UUID, PlayerUpdate>(entries, container,
                    [](const std::pair<const UUID, PlayerUpdate>& p, WriteContainer& c)
                    {
                        WriteData<UUID>(p.first, c);
                        WriteOptional<Chat>(p.second.GetDisplayName(), c);
                    }
                );
                break;
            case PlayerInfoAction::RemovePlayer:
                WriteMap<UUID, PlayerUpdate>(entries, container,
                    [](const std::pair<const UUID, PlayerUpdate>& p, WriteContainer& c)
                    {
                        WriteData<UUID>(p.first, c);
                    }
                );
                break;
            default:
                break;
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["action"] = action;
            output["entries"] = Json::Array();

            switch (action)
            {
            case PlayerInfoAction::AddPlayer:
                for (const auto& p : entries)
                {
                    Json::Value entry;
                    entry["uuid"] = p.first;
                    entry["player_info"] = p.second.Serialize();
                    output["entries"].push_back(entry);
                }
                break;
            case PlayerInfoAction::UpdateGameMode:
                for (const auto& p : entries)
                {
                    Json::Value entry;
                    entry["uuid"] = p.first;
                    entry["game_mode"] = p.second.GetGameMode();
                    output["entries"].push_back(entry);
                }
                break;
            case PlayerInfoAction::UpdateLatency:
                for (const auto& p : entries)
                {
                    Json::Value entry;
                    entry["uuid"] = p.first;
                    entry["latency"] = p.second.GetLatency();
                    output["entries"].push_back(entry);
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
                    output["entries"].push_back(entry);
                }
                break;
            case PlayerInfoAction::RemovePlayer:
                for (const auto& p : entries)
                {
                    output["entries"].push_back(p.first);
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
#endif
