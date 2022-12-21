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
#include "protocolCraft/Types/Bitset.hpp"

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

        RemoteChatSessionData chat_session;

        int game_mode;

        bool listed;

        int latency;

        Chat display_name;
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
            Bitset<static_cast<size_t>(PlayerInfoUpdateAction::NUM_PLAYERINFOUPDATEACTION)> bitset;
            bitset.Read(iter, length);
            actions.clear();
            for (size_t i = 0; i < static_cast<int>(PlayerInfoUpdateAction::NUM_PLAYERINFOUPDATEACTION); ++i)
            {
                if (bitset.bitset[i])
                {
                    actions.push_back(static_cast<PlayerInfoUpdateAction>(i));
                }
            }

            const int entries_length = ReadData<VarInt>(iter, length);
            for (size_t i = 0; i < entries_length; ++i)
            {
                const UUID uuid = ReadData<UUID>(iter, length);
                PlayerInfoUpdateEntry& entry = entries[uuid];
                for (size_t a = 0; a < actions.size(); ++a)
                {
                    switch (actions[a])
                    {
                    case PlayerInfoUpdateAction::AddPlayer:
                    {
                        entry.game_profile.SetUUID(uuid);
                        entry.game_profile.SetName(ReadData<std::string>(iter, length));
                        const int properties_length = ReadData<VarInt>(iter, length);
                        std::map<std::string, GameProfileProperty> properties;
                        for (size_t i = 0; i < properties_length; ++i)
                        {
                            GameProfileProperty prop;
                            prop.Read(iter, length);
                            properties[prop.GetName()] = prop;
                        }
                        entry.game_profile.SetProperties(properties);
                        break;
                    }
                    case PlayerInfoUpdateAction::InitializeChat:
                    {
                        const bool has_chat_session = ReadData<bool>(iter, length);
                        if (has_chat_session)
                        {
                            entry.chat_session.Read(iter, length);
                        }
                        break;
                    }
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
                    {
                        const bool has_display_name = ReadData<bool>(iter, length);
                        if (has_display_name)
                        {
                            entry.display_name.Read(iter, length);
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            Bitset<static_cast<size_t>(PlayerInfoUpdateAction::NUM_PLAYERINFOUPDATEACTION)> bitset;
            for (size_t i = 0; i < actions.size(); ++i)
            {
                bitset.bitset.set(static_cast<int>(actions[i]), true);
            }
            bitset.Write(container);

            WriteData<VarInt>(static_cast<int>(entries.size()), container);
            for (auto it = entries.begin(); it != entries.end(); ++it)
            {
                WriteData<UUID>(it->first, container);
                for (size_t a = 0; a < actions.size(); ++a)
                {
                    switch (actions[a])
                    {
                    case PlayerInfoUpdateAction::AddPlayer:
                        WriteData<std::string>(it->second.game_profile.GetName(), container);
                        WriteData<VarInt>(it->second.game_profile.GetProperties().size(), container);
                        for (auto it2 = it->second.game_profile.GetProperties().begin(); it2 != it->second.game_profile.GetProperties().end(); ++it)
                        {
                            it2->second.Write(container);
                        }
                        break;
                    case PlayerInfoUpdateAction::InitializeChat:
                    {
                        const bool has_chat_session = it->second.chat_session.GetProfilePublicKey().GetKey().size() > 0;
                        WriteData<bool>(has_chat_session, container);
                        if (has_chat_session)
                        {
                            it->second.chat_session.Write(container);
                        }
                        break;
                    }
                    case PlayerInfoUpdateAction::UpdateGameMode:
                        WriteData<VarInt>(it->second.game_mode, container);
                        break;
                    case PlayerInfoUpdateAction::UpdateListed:
                        WriteData<bool>(it->second.listed, container);
                        break;
                    case PlayerInfoUpdateAction::UpdateLatency:
                        WriteData<VarInt>(it->second.latency, container);
                        break;
                    case PlayerInfoUpdateAction::UpdateDisplayName:
                    {
                        const bool has_display_name = !it->second.display_name.GetRawText().empty();
                        WriteData<bool>(has_display_name, container);
                        if (has_display_name)
                        {
                            it->second.display_name.Write(container);
                        }
                        break;
                    }
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
            for (size_t i = 0; i < actions.size(); ++i)
            {
                output["actions"].push_back(static_cast<int>(actions[i]));
            }

            output["entries"] = nlohmann::json::array();
            for (auto it = entries.begin(); it != entries.end(); ++it)
            {
                nlohmann::json entry = nlohmann::json::object();
                entry["uuid"] = it->first;
                for (size_t a = 0; a < actions.size(); ++a)
                {
                    switch (actions[a])
                    {
                    case PlayerInfoUpdateAction::AddPlayer:
                        entry["game_profile"] = it->second.game_profile.Serialize();
                        break;
                    case PlayerInfoUpdateAction::InitializeChat:
                        if (it->second.chat_session.GetProfilePublicKey().GetKey().size() > 0)
                        {
                            entry["chat_session"] = it->second.chat_session.Serialize();
                        }
                        break;
                    case PlayerInfoUpdateAction::UpdateGameMode:
                        entry["game_mode"] = it->second.game_mode;
                        break;
                    case PlayerInfoUpdateAction::UpdateListed:
                        entry["listed"] = it->second.listed;
                        break;
                    case PlayerInfoUpdateAction::UpdateLatency:
                        entry["latency"] = it->second.latency;
                        break;
                    case PlayerInfoUpdateAction::UpdateDisplayName:
                        if (!it->second.display_name.GetRawText().empty())
                        {
                            entry["display_name"] = it->second.display_name.Serialize();
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
