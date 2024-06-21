#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include <string>
#include <map>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
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

        int game_mode = 0;

        bool listed = false;

        int latency = 0;

        std::optional<Chat> display_name;
    };

    class ClientboundPlayerInfoUpdatePacket : public BaseMessage<ClientboundPlayerInfoUpdatePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Player Info Update";

        DECLARE_FIELDS(
            (std::vector<PlayerInfoUpdateAction>, std::map<UUID, PlayerInfoUpdateEntry>),
            (Actions,                             Entries)
        );

        GETTER_SETTER(Actions);
        GETTER_SETTER(Entries);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            // Get the number of bits to encode all possible actions in a bitset
            constexpr size_t bitset_size = static_cast<size_t>(PlayerInfoUpdateAction::NUM_PLAYERINFOUPDATEACTION);
            std::bitset<bitset_size> bitset = ReadData<std::bitset<bitset_size>>(iter, length);
            std::vector<PlayerInfoUpdateAction> actions;
            for (size_t i = 0; i < bitset_size; ++i)
            {
                if (bitset[i])
                {
                    actions.push_back(static_cast<PlayerInfoUpdateAction>(i));
                }
            }
            SetActions(actions);

            std::map<UUID, PlayerInfoUpdateEntry> entries;
            const int entries_length = ReadData<VarInt>(iter, length);
            for (int i = 0; i < entries_length; ++i)
            {
                const UUID uuid = ReadData<UUID>(iter, length);
                PlayerInfoUpdateEntry& entry = entries[uuid];
                for (const auto a : actions)
                {
                    switch (a)
                    {
                    case PlayerInfoUpdateAction::AddPlayer:
                        entry.game_profile.SetUuid(uuid);
                        entry.game_profile.SetName(ReadData<std::string>(iter, length));
                        entry.game_profile.SetProperties(ReadData<std::vector<GameProfileProperty>>(iter, length));
                        break;
                    case PlayerInfoUpdateAction::InitializeChat:
                        entry.chat_session = ReadData<std::optional<RemoteChatSessionData>>(iter, length);
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
                        entry.display_name = ReadData<std::optional<Chat>>(iter, length);
                        break;
                    default:
                        break;
                    }
                }
            }
            SetEntries(entries);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            constexpr size_t bitset_size = static_cast<size_t>(PlayerInfoUpdateAction::NUM_PLAYERINFOUPDATEACTION);
            std::bitset<bitset_size> bitset;
            for (const auto a : GetActions())
            {
                bitset.set(static_cast<size_t>(a), true);
            }
            WriteData<std::bitset<bitset_size>>(bitset, container);

            WriteData<VarInt>(static_cast<int>(GetEntries().size()), container);
            for (const auto& p : GetEntries())
            {
                WriteData<UUID>(p.first, container);
                for (const auto a : GetActions())
                {
                    switch (a)
                    {
                    case PlayerInfoUpdateAction::AddPlayer:
                        WriteData<std::string>(p.second.game_profile.GetName(), container);
                        WriteData<std::vector<GameProfileProperty>>(p.second.game_profile.GetProperties(), container);
                        break;
                    case PlayerInfoUpdateAction::InitializeChat:
                        WriteData<std::optional<RemoteChatSessionData>>(p.second.chat_session, container);
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
                        WriteData<std::optional<Chat>>(p.second.display_name, container);
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Actions)])] = GetActions();

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Entries)])] = Json::Array();
            for (const auto& p : GetEntries())
            {
                Json::Value entry = Json::Object();
                entry["uuid"] = p.first;
                for (const auto a : GetActions())
                {
                    switch (a)
                    {
                    case PlayerInfoUpdateAction::AddPlayer:
                        entry["game_profile"] = p.second.game_profile;
                        break;
                    case PlayerInfoUpdateAction::InitializeChat:
                        if (p.second.chat_session.has_value())
                        {
                            entry["chat_session"] = p.second.chat_session.value();
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
                            entry["display_name"] = p.second.display_name.value();
                        }
                        break;
                    default:
                        break;
                    }
                }
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Entries)])].push_back(entry);
            }

            return output;
        }
    };
} //ProtocolCraft
#endif
