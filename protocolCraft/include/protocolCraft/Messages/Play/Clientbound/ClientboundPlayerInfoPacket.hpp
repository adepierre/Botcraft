#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
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
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x32;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x37;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Player Info";

        DECLARE_FIELDS_TYPES(DiffType<PlayerInfoAction, VarInt>, std::map<UUID, PlayerUpdate>);
        DECLARE_FIELDS_NAMES(Action,                             Entries);

        GETTER_SETTER(Action);
        GETTER_SETTER(Entries);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetAction(ReadData<PlayerInfoAction, VarInt>(iter, length));
            switch (GetAction())
            {
            case PlayerInfoAction::AddPlayer:
                SetEntries(ReadData<std::map<UUID, PlayerUpdate>>(iter, length));
                break;
            case PlayerInfoAction::UpdateGameMode:
                // Special case, partial read
                SetEntries(ReadMap<UUID, PlayerUpdate>(iter, length,
                    [](ReadIterator& i, size_t& l)
                    {
                        const UUID uuid = ReadData<UUID>(i, l);
                        PlayerUpdate player_update;
                        player_update.SetGameMode(ReadData<VarInt>(i, l));

                        return std::make_pair(uuid, player_update);
                    }
                ));
                break;
            case PlayerInfoAction::UpdateLatency:
                // Special case, partial read
                SetEntries(ReadMap<UUID, PlayerUpdate>(iter, length,
                    [](ReadIterator& i, size_t& l)
                    {
                        const UUID uuid = ReadData<UUID>(i, l);
                        PlayerUpdate player_update;
                        player_update.SetLatency(ReadData<VarInt>(i, l));

                        return std::make_pair(uuid, player_update);
                    }
                ));
                break;
            case PlayerInfoAction::UpdateDisplayName:
                // Special case, partial read
                SetEntries(ReadMap<UUID, PlayerUpdate>(iter, length,
                    [](ReadIterator& i, size_t& l)
                    {
                        const UUID uuid = ReadData<UUID>(i, l);
                        PlayerUpdate player_update;
                        player_update.SetDisplayName(ReadData<std::optional<Chat>>(i, l));

                        return std::make_pair(uuid, player_update);
                    }
                ));
                break;
            case PlayerInfoAction::RemovePlayer:
                // Special case, partial read
                SetEntries(ReadMap<UUID, PlayerUpdate>(iter, length,
                    [](ReadIterator& i, size_t& l)
                    {
                        const UUID uuid = ReadData<UUID>(i, l);

                        return std::make_pair(uuid, PlayerUpdate());
                    }
                ));
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<PlayerInfoAction, VarInt>(GetAction(), container);
            switch (GetAction())
            {
            case PlayerInfoAction::AddPlayer:
                WriteData<std::map<UUID, PlayerUpdate>>(GetEntries(), container);
                break;
            case PlayerInfoAction::UpdateGameMode:
                // Special case, partial write
                WriteMap<UUID, PlayerUpdate>(GetEntries(), container,
                    [](const std::pair<const UUID, PlayerUpdate>& p, WriteContainer& c)
                    {
                        WriteData<UUID>(p.first, c);
                        WriteData<VarInt>(p.second.GetGameMode(), c);
                    }
                );
                break;
            case PlayerInfoAction::UpdateLatency:
                // Special case, partial write
                WriteMap<UUID, PlayerUpdate>(GetEntries(), container,
                    [](const std::pair<const UUID, PlayerUpdate>& p, WriteContainer& c)
                    {
                        WriteData<UUID>(p.first, c);
                        WriteData<VarInt>(p.second.GetLatency(), c);
                    }
                );
                break;
            case PlayerInfoAction::UpdateDisplayName:
                // Special case, partial write
                WriteMap<UUID, PlayerUpdate>(GetEntries(), container,
                    [](const std::pair<const UUID, PlayerUpdate>& p, WriteContainer& c)
                    {
                        WriteData<UUID>(p.first, c);
                        WriteData<std::optional<Chat>>(p.second.GetDisplayName(), c);
                    }
                );
                break;
            case PlayerInfoAction::RemovePlayer:
                // Special case, partial write
                WriteMap<UUID, PlayerUpdate>(GetEntries(), container,
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

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Action)])] = GetAction();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Entries)])] = Json::Array();

            switch (GetAction())
            {
            case PlayerInfoAction::AddPlayer:
                for (const auto& p : GetEntries())
                {
                    output[std::string(json_names[static_cast<size_t>(FieldsEnum::Entries)])].push_back({ {"uuid", p.first}, {"player_info", p.second} });
                }
                break;
            case PlayerInfoAction::UpdateGameMode:
                for (const auto& p : GetEntries())
                {
                    output[std::string(json_names[static_cast<size_t>(FieldsEnum::Entries)])].push_back({ {"uuid", p.first}, {"game_mode", p.second.GetGameMode()} });
                }
                break;
            case PlayerInfoAction::UpdateLatency:
                for (const auto& p : GetEntries())
                {
                    output[std::string(json_names[static_cast<size_t>(FieldsEnum::Entries)])].push_back({ {"uuid", p.first}, {"latency", p.second.GetLatency()} });
                }
                break;
            case PlayerInfoAction::UpdateDisplayName:
                for (const auto& p : GetEntries())
                {
                    Json::Value entry;
                    entry["uuid"] = p.first;
                    if (p.second.GetDisplayName().has_value())
                    {
                        entry["display_name"] = p.second.GetDisplayName().value().Serialize();
                    }
                    output[std::string(json_names[static_cast<size_t>(FieldsEnum::Entries)])].push_back(entry);
                }
                break;
            case PlayerInfoAction::RemovePlayer:
                for (const auto& p : GetEntries())
                {
                    output[std::string(json_names[static_cast<size_t>(FieldsEnum::Entries)])].push_back(p.first);
                }
                break;
            default:
                break;
            }

            return output;
        }
    };
} //ProtocolCraft
#endif
