#if PROTOCOL_VERSION > 760
#pragma once

#include <string>
#include <map>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/PlayerUpdate.hpp"
#include "protocolCraft/Types/GameProfile/GameProfile.hpp"
#include "protocolCraft/Types/GameProfile/GameProfileProperty.hpp"
#include "protocolCraft/Types/Chat/RemoteChatSessionData.hpp"

namespace ProtocolCraft
{
    enum class PlayerInfoUpdateAction
    {
        AddPlayer = 0,
        InitializeChat,
        UpdateGameMode,
        UpdateListed,
        UpdateLatency,
        UpdateDisplayName,
        NUM_PLAYERINFOUPDATEACTION
    };

    struct PlayerInfoUpdateEntry
    {
        GameProfile game_profile;

        std::optional<RemoteChatSessionData> chat_session;

        int game_mode;

        bool listed;

        int latency;

        std::optional<Chat> display_name;
    };

    class ClientboundPlayerInfoUpdatePacket : public BaseMessage<ClientboundPlayerInfoUpdatePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 761 // 1.19.3
            return 0x36;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Info Update";
        }

        virtual ~ClientboundPlayerInfoUpdatePacket() override
        {

        }

        void SetActions(const std::vector<PlayerInfoUpdateAction>& actions_)
        {
            actions = actions_;
        }

        void SetEntries(const std::map<UUID, PlayerInfoUpdateEntry>& entries_)
        {
            entries = entries_;
        }


        const std::vector<PlayerInfoUpdateAction> GetActions() const
        {
            return actions;
        }

        const std::map<UUID, PlayerInfoUpdateEntry>& GetEntries() const
        {
            return entries;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            // Get the number of bits to encode all possible actions in a bitset
            constexpr size_t bitset_size = static_cast<size_t>(PlayerInfoUpdateAction::NUM_PLAYERINFOUPDATEACTION);
            std::bitset<bitset_size> bitset = ReadBitset<bitset_size>(iter, length);
            actions.clear();
            for (size_t i = 0; i < bitset_size; ++i)
            {
                if (bitset[i])
                {
                    actions.push_back(static_cast<PlayerInfoUpdateAction>(i));
                }
            }

            const int entries_length = ReadData<VarInt>(iter, length);
            for (size_t i = 0; i < entries_length; ++i)
            {
                const UUID uuid = ReadData<UUID>(iter, length);
                PlayerInfoUpdateEntry& entry = entries[uuid];
                for (const auto a : actions)
                {
                    switch (a)
                    {
                    case PlayerInfoUpdateAction::AddPlayer:
                    {
                        entry.game_profile.SetUUID(uuid);
                        entry.game_profile.SetName(ReadData<std::string>(iter, length));
                        entry.game_profile.SetProperties(
                            ReadMap<std::string, GameProfileProperty>(iter, length,
                                [](ReadIterator& i, size_t& l)
                                {
                                    const GameProfileProperty prop = ReadData<GameProfileProperty>(i, l);
                                    return std::make_pair(prop.GetName(), prop);
                                }
                                )
                        );
                        break;
                    }
                    case PlayerInfoUpdateAction::InitializeChat:
                        entry.chat_session = ReadOptional<RemoteChatSessionData>(iter, length);
                        break;
                    case PlayerInfoUpdateAction::UpdateGameMode:
                        entry.game_mode = ReadData<VarInt>(iter, length);
                        break;
                    case PlayerInfoUpdateAction::UpdateListed:
                        entry.listed = ReadData<bool>(iter, length);
                        break;
                    case PlayerInfoUpdateAction::UpdateLatency:
                        entry.latency = ReadData<VarInt>(iter, length);
                        break;
                    case PlayerInfoUpdateAction::UpdateDisplayName:
                        entry.display_name = ReadOptional<Chat>(iter, length);
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            constexpr size_t bitset_size = static_cast<size_t>(PlayerInfoUpdateAction::NUM_PLAYERINFOUPDATEACTION);
            std::bitset<bitset_size> bitset;
            for (const auto a : actions)
            {
                bitset.set(static_cast<size_t>(a), true);
            }
            WriteBitset<bitset_size>(bitset, container);

            WriteData<VarInt>(static_cast<int>(entries.size()), container);
            for (const auto& p : entries)
            {
                WriteData<UUID>(p.first, container);
                for (const auto a : actions)
                {
                    switch (a)
                    {
                    case PlayerInfoUpdateAction::AddPlayer:
                        WriteData<std::string>(p.second.game_profile.GetName(), container);
                        WriteMap<std::string, GameProfileProperty>(p.second.game_profile.GetProperties(), container,
                            [](const std::pair<const std::string, GameProfileProperty>& i, WriteContainer& c)
                            {
                                WriteData<GameProfileProperty>(i.second, c);
                            }
                        );
                        break;
                    case PlayerInfoUpdateAction::InitializeChat:
                        WriteOptional<RemoteChatSessionData>(p.second.chat_session, container);
                        break;
                    case PlayerInfoUpdateAction::UpdateGameMode:
                        WriteData<VarInt>(p.second.game_mode, container);
                        break;
                    case PlayerInfoUpdateAction::UpdateListed:
                        WriteData<bool>(p.second.listed, container);
                        break;
                    case PlayerInfoUpdateAction::UpdateLatency:
                        WriteData<VarInt>(p.second.latency, container);
                        break;
                    case PlayerInfoUpdateAction::UpdateDisplayName:
                        WriteOptional<Chat>(p.second.display_name, container);
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["actions"] = nlohmann::json::array();
            for (const auto a : actions)
            {
                output["actions"].push_back(static_cast<int>(a));
            }

            output["entries"] = nlohmann::json::array();
            for (const auto& p : entries)
            {
                nlohmann::json entry = nlohmann::json::object();
                entry["uuid"] = p.first;
                for (const auto a : actions)
                {
                    switch (a)
                    {
                    case PlayerInfoUpdateAction::AddPlayer:
                        entry["game_profile"] = p.second.game_profile.Serialize();
                        break;
                    case PlayerInfoUpdateAction::InitializeChat:
                        if (p.second.chat_session.has_value())
                        {
                            entry["chat_session"] = p.second.chat_session.value().Serialize();
                        }
                        break;
                    case PlayerInfoUpdateAction::UpdateGameMode:
                        entry["game_mode"] = p.second.game_mode;
                        break;
                    case PlayerInfoUpdateAction::UpdateListed:
                        entry["listed"] = p.second.listed;
                        break;
                    case PlayerInfoUpdateAction::UpdateLatency:
                        entry["latency"] = p.second.latency;
                        break;
                    case PlayerInfoUpdateAction::UpdateDisplayName:
                        if (p.second.display_name.has_value())
                        {
                            entry["display_name"] = p.second.display_name.value().Serialize();
                        }
                        break;
                    default:
                        break;
                    }
                }
                output["entries"].push_back(entry);
            }

            return output;
        }

    private:
        std::vector<PlayerInfoUpdateAction> actions;
        std::map<UUID, PlayerInfoUpdateEntry> entries;
    };
} //ProtocolCraft
#endif
